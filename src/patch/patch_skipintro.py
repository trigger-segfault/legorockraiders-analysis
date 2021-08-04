#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Apply patch to LEGO Rock Raiders masterpiece executable to make all opening intros skippable.
"""

__version__ = '1.0.0'
__date__    = '2021-07-24'
__author__  = 'Robert Jordan'

__all__ = ['patch_file_skipintro', 'patch_data_skipintro', 'apply_patch_skipintro']

#######################################################################################

import traceback
from typing import Optional


#######################################################################################

#region ## CONSTANTS ##

###  NEG   EAX
###  SBB   EAX,EAX
###  NEG   EAX
###  PUSH  EAX
###1 PUSH  [004a4b5c] = "LegoAvi"
###1 CALL  void Boot_loadAVIProperty(char*,BOOL)
###2 PUSH  [004a4b24] = "LMILogo"
###2 CALL  void Boot_loadSplashProperty(char*,BOOL,char*)
# search for both calls to intro functions, where the skippably boolean is not constant
SEARCH_DAT1 = bytes.fromhex('f7 d8 1b c0 f7 d8 50 68 5c 4b 4a 00 e8 22 56 ff ff')
SEARCH_DAT2 = bytes.fromhex('f7 d8 1b c0 f7 d8 50 68 24 4b 4a 00 e8 82 54 ff ff')

###-  NEG   EAX
###-  SBB   EAX,EAX
###-  NEG   EAX
###-  PUSH  EAX
###+  NOP
###+  NOP
###+  NOP
###+  NOP
###+  NOP
###+  PUSH  0x1
# strip useless operations and push constant 0x1 (true)
REPL_OFF   = 0x0
ORIG_DAT   = bytes.fromhex('f7 d8 1b c0 f7 d8 50')
REPL_DAT   = bytes.fromhex('90 90 90 90 90 6a 01')

#endregion

#######################################################################################

#region ## APPLY PATCH ##

def apply_patch(data:bytearray) -> None:
    if not isinstance(data, bytearray):
        raise TypeError(f'apply_patch() argument must be bytearray, not {data.__class__.__name__}')
    
    # keep track of length to ensure everything went correctly
    orig_len = len(data)
    
    # make sure we found our data,
    # and that there's only one appearance of the pattern we're searching for
    offset1 = data.find(SEARCH_DAT1)
    assert(offset1 != -1 and data.count(SEARCH_DAT1) == 1)
    offset2 = data.find(SEARCH_DAT2)
    assert(offset2 != -1 and data.count(SEARCH_DAT2) == 1)

    # create shorthands for all offsets
    off1 = offset1 + REPL_OFF
    off2 = offset2 + REPL_OFF

    # replace instructions
    assert(data[off1 : off1+len(REPL_DAT)] == ORIG_DAT)
    data[off1 : off1+len(REPL_DAT)] = REPL_DAT
    assert(data[off2 : off2+len(REPL_DAT)] == ORIG_DAT)
    data[off2 : off2+len(REPL_DAT)] = REPL_DAT

    # ensure the length of the file never changed
    assert(len(data) == orig_len)

    # done!
    
#endregion

#######################################################################################

#region ## PATCH FILE/DATA ##

def patch_data(data:bytes) -> bytearray:
    data = bytearray(data)
    apply_patch(data)
    return data

def patch_file(src_file:str, dst_file:Optional[str]=None) -> None:
    # overwrite src_file if dst_file was not specified
    if dst_file is None:
        dst_file = src_file
    
    # Read source file
    with open(src_file, 'rb') as f:
        data = f.read()
    
    data = patch_data(data)
    
    with open(dst_file, 'wb+') as f:
        f.write(data)
        f.flush()

#endregion

#######################################################################################

# assign import * names
apply_patch_skipintro = apply_patch
patch_data_skipintro = patch_data
patch_file_skipintro = patch_file

#######################################################################################

#region ## MAIN FUNCTION ##

def main(argv:Optional[list]=None) -> int:
    import os

    BACKUP_CONST = '_orig'

    #region ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='Apply patch to LEGO Rock Raiders masterpiece executable make all opening intros skippable.',
        add_help=True)
    
    parser.add_argument('input', metavar='INPUTEXE', help='original executable to patch (LegoRR.exe)')
    oparser = parser.add_argument_group('output options')
    ogroup = oparser.add_mutually_exclusive_group(required=False)
    ogroup.add_argument('-o', '--output', metavar='OUTPUTEXE', default=None, help='write to new executable output file')
    ogroup.add_argument('-n', '--name', metavar='OUTPUTNAME', dest='rename', default=None, help='write to new executable name in same directory')
    ogroup.add_argument('-r', '--replace', action='store_true', default=False, help='overwrite original executable')
    ogroup.add_argument('-b', '--backup', action='store_true', default=False, help=f'overwrite original executable and create *{BACKUP_CONST}.exe backup')
    parser.add_argument('-q', '--quiet', action='store_true', default=False, help='don\'t print actions being performed')
    parser.add_argument('-T', '--test', action='store_true', default=False, help='test patch without saving any changes')

    #endregion

    ###########################################################################

    #region ## PARSER VALIDATION ##

    args = parser.parse_args(argv)

    input = args.input
    output = None
    backup = None
    if args.output is not None:
        output = args.output
    elif args.rename is not None:
        output = os.path.join(os.path.dirname(input), args.rename)
    elif args.replace or args.backup:
        output = input
        if args.backup:
            basepath, ext = os.path.splitext(input)
            backup = basepath + BACKUP_CONST + ext
    
    test = args.test
    if not test and not output:
        parser.error('destination executable file must be specified!')
    if not input:
        parser.error('input executable file path is empty!')
    if not os.path.isfile(input):
        parser.error('input executable file not found!')
    if output and os.path.isdir(output):
        parser.error('destination executable file cannot be directory!')
    
    verbose = args.test or not args.quiet

    #endregion

    ###########################################################################

    if verbose: print(f'Loading: {input}')
    with open(input, 'rb') as f:
        data = f.read()
    
    if backup:
        if verbose: print(f'Backup:  {backup}')
        if not test:
            with open(backup, 'wb+') as f:
                f.write(data)
                f.flush()

    if verbose: print('Applying patch...')
    try:
        data = patch_data(data)
    except AssertionError as ex:
        print('Erroring patching executable, unexpected data found!')
        # traceback.print_exc()
        return 1

    if output:
        if verbose: print(f'Saving:  {output}')
        if not test:
            with open(output, 'wb+') as f:
                f.write(data)
                f.flush()

    if verbose: print('Done!')

    return 0

#endregion


###########################################################################

del Optional  # cleanup declaration-only imports


## MAIN CONDITION ##

if __name__ == '__main__':
    exit(main())
