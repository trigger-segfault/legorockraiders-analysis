#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Apply patch to LEGO Rock Raiders masterpiece executable to fix sound effect groups.
"""

__version__ = '1.0.0'
__date__    = '2021-06-26'
__author__  = 'Robert Jordan'

__all__ = ['patch_file_sfxgroup', 'patch_data_sfxgroup', 'apply_patch_sfxgroup']

#######################################################################################

from typing import Optional


#######################################################################################

#region ## CONSTANTS ##

### CALL       lego::snd::SFX_Load (FUN_0047ab30)
# search for call to this function which returns our sfxIndex
#  (only ever called by this function)
SEARCH_DAT  = bytes.fromhex('e8 c2 5a 01 00')

###-  JBE        LAB_004650c6
###+  JBE        LAB_004650c8
# modify jump on `numParts == 0`
#  (offset + 0x2 after insert)
REPL_OFF1   = -0x66
ORIG_DAT1   = bytes.fromhex('0f 86 bd 00 00 00')
REPL_DAT1   = bytes.fromhex('0f 86 bf 00 00 00')
###-  MOV        dword ptr [EDI],EAX=>SFXProperty->sfxIndex   = ??
###-  JZ         LAB_004650a2
###+  MOV        EDX,EAX
###+  JZ         LAB_004650a4
# dont't write sfxIndex yet, instead save it to EDX register (which is not being used atm)
# modify jump on `sfxIndex == -1`
#  (offset + 0x2 after insert)
REPL_OFF2   =  0xb
ORIG_DAT2   = bytes.fromhex('89 07 74 2a')
REPL_DAT2   = bytes.fromhex('8b d0 74 2c')
###-  JNZ        LAB_00465017
###+  JNZ        LAB_00465017
# modify jump on `do {} while (numParts != 0)`
#  (offset - 0x2 after insert)
REPL_OFF3   = 0x55
ORIG_DAT3   = bytes.fromhex('0f 85 53 ff ff ff')
REPL_DAT3   = bytes.fromhex('0f 85 51 ff ff ff')
###+  MOV        dword ptr [EDI],EDX=>SFXProperty->sfxIndex   = ??
###   JMP        LAB_004650aa
# insert move instruction for `sfxIndex = EDX`
#  (original instruction register now assigns value of EDX, not EAX)
INSERT_OFF4 = 0x37 # (before)
INSERT_DAT4 = bytes.fromhex('89 17')
###   RET
###=  ??
###=  ??
###=  ??
# end of function, we need to shift everything by size of our inserted data (0x2)
#  (we have plenty of room with 0x90 INT3 padding bytes to overwrite)
END_OFF5    = 0x6a # (after RET)
ORIG_DAT5   = bytes.fromhex('90 90 90')

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
    offset = data.find(SEARCH_DAT)
    assert(offset != -1 and data.count(SEARCH_DAT) == 1)

    # create shorthands for all offsets
    off1 = offset + REPL_OFF1
    off2 = offset + REPL_OFF2
    off3 = offset + REPL_OFF3
    off4 = offset + INSERT_OFF4
    off5 = offset + END_OFF5

    # replace instructions
    assert(data[off1 : off1+len(REPL_DAT1)] == ORIG_DAT1)
    data[off1 : off1+len(REPL_DAT1)] = REPL_DAT1
    assert(data[off2 : off2+len(REPL_DAT2)] == ORIG_DAT2)
    data[off2 : off2+len(REPL_DAT2)] = REPL_DAT2
    assert(data[off3 : off3+len(REPL_DAT3)] == ORIG_DAT3)
    data[off3 : off3+len(REPL_DAT3)] = REPL_DAT3

    # ensure end of function
    assert(data[off5 : off5+len(ORIG_DAT5)] == ORIG_DAT5)
    # store a copy of data to shift (after insert)
    shift_dat = data[off4 : off5]

    # insert data (technically replace, so we don't offset the file contents)
    data[off4 : off4+len(INSERT_DAT4)] = INSERT_DAT4

    # finally store shifted data (offset by the size of inserted data)
    data[off4+len(INSERT_DAT4) : off5+len(INSERT_DAT4)] = shift_dat

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
apply_patch_sfxgroup = apply_patch
patch_data_sfxgroup = patch_data
patch_file_sfxgroup = patch_file

#######################################################################################

#region ## MAIN FUNCTION ##

def main(argv:Optional[list]=None) -> int:
    import os

    BACKUP_CONST = '_orig'

    #region ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='Apply patch to LEGO Rock Raiders masterpiece executable to fix sound effect groups.',
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
