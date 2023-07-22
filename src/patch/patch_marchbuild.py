#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Apply patches to LEGO Rock Raiders March build executable to get it up and running.
"""

__version__ = '1.0.0'
__date__    = '2023-07-22'
__author__  = 'Robert Jordan'

__all__ = ['patch_file_marchbuild', 'patch_data_marchbuild', 'apply_patch_marchbuild']

#######################################################################################

import traceback
from typing import Optional


#######################################################################################

#region ## CONSTANTS ##

# Starting address: 0048d438
SLASH_ORIG_DAT = b'\Interface\Panels\encycPanel.bmp'
SLASH_REPL_DAT = SLASH_ORIG_DAT[1:] + b'\x00'

assert(len(SLASH_ORIG_DAT) == len(SLASH_REPL_DAT))

# Starting address: 0046dacc
DISSOLVECMP_ORIG_DAT = bytes.fromhex('83 3d 8c 78 4f 00 0a') # if (lwsGlobs_staticDissolveCount == 10)
DISSOLVECMP_REPL_DAT = bytes.fromhex('83 3d 8c 78 4f 00 64') # if (lwsGlobs_staticDissolveCount == 100)

assert(len(DISSOLVECMP_ORIG_DAT) == len(DISSOLVECMP_REPL_DAT))

# Starting address: 0046daef
# fVar15 = (float10)std::atof(local_96c);
DISSOLVESTART_SEARCH_DAT = bytes.fromhex('8b 95 98 f6 ff ff  52  e8 35 9d 00 00  83 c4 04  a1 8c 78 4f 00')
# lwsGlobs_staticDissolveCount += 1;
#DISSOLVEEND_SEARCH_DAT   = bytes.fromhex('8b 0d 8c 78 4f 00')
# local_980[7] = NULL;
DISSOLVEEND_SEARCH_DAT   = bytes.fromhex('8b 95 84 f6 ff ff  c7 42 1c 00 00 00 00  e9 27 01 00 00  68 d0 82 4b 00')
NOP = 0x90

#endregion

#######################################################################################

#region ## APPLY PATCH ##

def apply_patch(data:bytearray) -> None:
    if not isinstance(data, bytearray):
        raise TypeError(f'apply_patch() argument must be bytearray, not {data.__class__.__name__}')
    
    # keep track of length to ensure everything went correctly
    orig_len = len(data)

    # Fix root slash in hardcoded filepath
    # Starting address: 0048d438
    assert(data.count(SLASH_ORIG_DAT) == 1)
    data.replace(SLASH_ORIG_DAT, SLASH_REPL_DAT, 1)

    # Remove usage of ObjDissolve #.### because it's not actually used
    # Change ObjDissolve limit from 10 to 100
    # Starting address: 0046dacc
    assert(data.count(DISSOLVECMP_ORIG_DAT) == 1)
    off1 = data.find(DISSOLVECMP_ORIG_DAT)
    data.replace(DISSOLVECMP_ORIG_DAT, DISSOLVECMP_REPL_DAT, 1)

    # Prevent writing to staticDissolveLevel array
    # Starting address: 0046daef
    # NOP SLIDE! WOOOOO
    start = data.find(DISSOLVESTART_SEARCH_DAT)
    end   = data.find(DISSOLVEEND_SEARCH_DAT, start + 1)
    assert(start != -1)
    assert(end   != -1)
    assert(data.count(DISSOLVESTART_SEARCH_DAT) == 1)
    assert(data.count(DISSOLVEEND_SEARCH_DAT, start + 1) == 1)
    for i in range(start, end):
        data[i] = NOP

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
apply_patch_marchbuild = apply_patch
patch_data_marchbuild = patch_data
patch_file_marchbuild = patch_file


#######################################################################################

#region ## MAIN FUNCTION ##

def main(argv:Optional[list]=None) -> int:
    import os

    BACKUP_CONST = '_orig'

    #region ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='Apply patches to LEGO Rock Raiders March build executable to get it up and running.',
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
