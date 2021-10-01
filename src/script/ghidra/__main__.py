#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Ghidra helper scripts.
"""

__version__ = '0.0.1'
__date__    = '2021-09-30'
__author__  = 'Robert Jordan'

__all__ = ['main']

#######################################################################################

import os, re
from struct import *
import traceback
from collections import namedtuple
from struct import Struct
from typing import Optional, Pattern


#######################################################################################

# print('__main__.py', '__name__ =', __name__)

from . import ghidra_export as ge

DATE_NAME = r"<date>"
SUFFIX_NAME = r"<suffix>"

# print('ge =', dir(ge))
DATE_PAT = r"(?P<y>[0-9]{4})-(?P<m>[0-9]{2})-(?P<d>[0-9]{2})"
SUFFIX_PAT = r"(?P<suffix>\-[A-Za-z]+)?"

def create_filepattern(name:str) -> Pattern:
    name = re.escape(name)
    name = DATE_PAT.join(name.split(re.escape(DATE_NAME)))
    name = SUFFIX_PAT.join(name.split(re.escape(SUFFIX_NAME)))
    return re.compile(name, re.IGNORECASE | re.UNICODE)

def find_filepattern(name:str) -> Optional[str]:
    dirname,filename = os.path.split(name)
    if not dirname: dirname = '.'
    pattern = create_filepattern(filename)
    matches = [file for file in os.listdir(dirname) if pattern.fullmatch(file)]
    # for file in os.listdir(dirname):
    #     if pattern.fullmatch(file):
    #         return file
    if matches:
        sorted_matches = list(sorted(matches, key=lambda x: os.path.splitext(x)[0], reverse=True))
        print('\n'.join(sorted_matches))
        return sorted_matches[0]
        # return list(sorted(matches, key=lambda x: os.path.splitext(x)[0], reverse=True))[0]
    return None

DATATYPES_ORDER = [ge.SymbolKind.PRIMITIVE, ge.SymbolKind.PRIMITIVE, ge.SymbolKind.PRIMITIVE, ge.SymbolKind.TYPEDEF, ge.SymbolKind.TYPEDEF, ge.SymbolKind.ENUM, ge.SymbolKind.FLAGS, ge.SymbolKind.UNION, ge.SymbolKind.STRUCT, ge.SymbolKind.VARIABLE, ge.SymbolKind.VARIABLE, ge.SymbolKind.FUNCTION, ge.SymbolKind.FUNCTION]

def sortby_datatypes(symbol:ge.Symbol) -> int:
    if isinstance(symbol, ge.DefineTypedefSymbol):
        idx = 1
    elif isinstance(symbol, ge.DefineValueSymbol):
        idx = 2
    else:
        idx = DATATYPES_ORDER.index(symbol.kind)
    #
    sortnum = idx
    if symbol.kind is ge.SymbolKind.TYPEDEF and symbol.is_function:
        sortnum += 1
    # if symbol.kind is ge.SymbolKind.TYPEDEF and not symbol.is_function:
    #     sortnum = idx + 1
    symname = symbol.name.lower()
    #
    if symbol.kind in (ge.SymbolKind.VARIABLE, ge.SymbolKind.FUNCTION):
        if symbol.address is None:
            sortnum += 1
            return f'{sortnum:02d}|{0xffffffff:08x}|{symname}'
        else:
            return f'{sortnum:02d}|{symbol.address:08x}|{symname}'
    else:
        #
        return f'{sortnum:02d}|{symname}'

def filter_noprimitive(symbol:ge.Symbol) -> bool:
    return symbol.kind is not ge.SymbolKind.PRIMITIVE

def filter_symbols(db:ge.SymbolDatabase, predicate=filter_noprimitive, key=sortby_datatypes, reverse:bool=False):
    if isinstance(predicate, ge.SymbolKind):
        symkind = predicate
        predicate = lambda s: s.kind is symkind
    if predicate is not None:
        syms = list(filter(predicate, db.symbols.values()))
    else:
        syms = list(db.symbols.values())
    # symsu = syms
    return list(sorted(syms, key=key, reverse=reverse))


#######################################################################################

#region ## MAIN FUNCTION ##

def main(argv:Optional[list]=None) -> int:
    import os

    BACKUP_CONST = '_orig'

    os.chdir('../export')

    #region ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='Ghidra helper scripts',
        add_help=True)

    subparsers = parser.add_subparsers()
    dtparser = subparsers.add_parser('datatypes')

    dtparser.add_argument('-i','--input', metavar=('HEADER','ASCII'), nargs=2, default=(f'LegoRR_{DATE_NAME}{SUFFIX_NAME}.h',f'LegoRR_{DATE_NAME}{SUFFIX_NAME}.txt'), help='header include file')
    #dtparser.add_argument('-o','--output', metavar='OUTPUT', default='LegoRR_<date>_formatted.h', help='formatted output header file')
    
    ##dtparser.add_argument('-i','--input', metavar='HEADER', default='../export/LegoRR_<date>.h', help='header include file')
    ##dtparser.add_argument('-o','--output', metavar='OUTPUT', default='../export/LegoRR_<date>_formatted.h', help='formatted output header file')

    oparser = dtparser.add_argument_group('output options')
    ogroup = oparser.add_mutually_exclusive_group(required=False)
    ogroup.add_argument('-o', '--output', metavar='OUTPUT', default=None, help='write to new header output file')
    ogroup.add_argument('-n', '--name', metavar='OUTPUTNAME', dest='rename', default=None, help='write to new header name in same directory')
    ogroup.add_argument('-a', '--append-name', metavar='OUTPUTNAME', dest='append', default=None, help='append text to new header name in same directory')
    ogroup.add_argument('-r', '--replace', action='store_true', default=False, help='overwrite original header')
    ogroup.add_argument('-b', '--backup', action='store_true', default=False, help=f'overwrite original header and create *{BACKUP_CONST}.h backup')
    
    dtparser.add_argument('-f','--filtered', action='store_true', default=False, help='Remove irrelevant datatypes')

    dtparser.add_argument('-q', '--quiet', action='store_true', default=False, help='don\'t print actions being performed')
    dtparser.add_argument('-T', '--test', action='store_true', default=False, help='test program without saving any changes')

    #endregion

    ###########################################################################

    #region ## PARSER VALIDATION ##

    args = parser.parse_args(argv)

    inputs = tuple(find_filepattern(f) for f in args.input)
    
    def determine_output(input): # -> (output, backup)
        output = args.output
        backup = None
        if args.output is not None:
            output = args.output
        elif args.rename is not None:
            output = os.path.join(os.path.dirname(input), args.rename)
        elif args.append is not None:
            output = args.append.join(os.path.splitext(input))
        elif args.replace or args.backup:
            output = input
            if args.backup:
                basepath, ext = os.path.splitext(input)
                backup = basepath + BACKUP_CONST + ext
        return output, backup

    output, backup = determine_output(args.input[0]) #inputs)
    # input = find_filepattern(args.input)
    # output = args.output
    # backup = None
    # if args.output is not None:
    #     output = args.output
    # elif args.rename is not None:
    #     output = os.path.join(os.path.dirname(input), args.rename)
    # elif args.append is not None:
    #     output = args.append.join(os.path.splitext(input))
    # elif args.replace or args.backup:
    #     output = input
    #     if args.backup:
    #         basepath, ext = os.path.splitext(input)
    #         backup = basepath + BACKUP_CONST + ext
    
    test = args.test
    if not test and not output:
        parser.error('destination executable file must be specified!')
    if not inputs[0] :
        parser.error('inputs[0] executable file path is empty!')
    if not inputs[1]:
        parser.error('inputs[1] executable file path is empty!')
    if not os.path.isfile(inputs[0]):
        parser.error('inputs[0] executable file not found!')
    if not os.path.isfile(inputs[1]):
        parser.error('inputs[1] executable file not found!')
    if output and os.path.isdir(output):
        parser.error('destination executable file cannot be directory!')
    
    verbose = args.test or not args.quiet
    filtered = args.filtered

    #endregion

    ###########################################################################

    EXCLUDE_FUNCTYPEDEFS = {'QsortCompare', 'PTOP_LEVEL_EXCEPTION_FILTER', '_PNH', 'WNDPROC', 'DLGPROC', 'MMIOPROC', 'FARPROC'}
    ALLOWED_TYPEDEFS = {'Mesh_TextureStateChangeData', 'Mesh_Texture', 'Material', 'Material_t', 'Animation', 'Animation_t', 'Movie', 'Movie_t'}
    FILTER_TAGS = {'DIRECTX','HIDDEN','RESOURCE','STD'}
    
    db = ge.LegoRRSymbolDatabase()
    db.populate_ghidra_primitives(preprocessor=True)

    datas = [None, None]

    if verbose: print(f'Loading: {inputs[0]}')
    with open(inputs[0], 'rt', encoding='utf-8') as f:
        datas[0] = f.read()
    if verbose: print(f'Loading: {inputs[1]}')
    with open(inputs[1], 'rt', encoding='utf-8') as f:
        datas[1] = f.read()
    
    # if backup:
    #     if verbose: print(f'Backup:  {backup}')
    #     if not test:
    #         with open(backup, 'wt+', encoding='utf-8') as f:
    #             f.write(data)
    #             f.flush()

    if verbose: print('Parsing header...')
    db.include_header(datas[0], filename=inputs[0])
    db.override_openlrr_display_names()
    if verbose: print('Parsing ascii...')
    db.include_ascii(datas[1], filename=inputs[1], guids=True)

    # with open()

    # if verbose: print('Formatting header...')
    # try:
    #     data = patch_data(data, new_name=args.dllname, verbose=verbose)
    # except AssertionError as ex:
    #     print('Erroring patching executable, unexpected data found!')
    #     if verbose:
    #         traceback.print_exc()
    #     return 1

    def is_filtered(symbol):
        if filtered:
            if symbol.hide:
                return True
            if symbol.tagged:
                return set(symbol.tagged.tags).intersection(FILTER_TAGS)
        return False
        # if filtered and symbol.hide: continue

    if output:
        if verbose: print(f'Saving:  {output}')
        if not test:
            with open(output, 'wt+', encoding='utf-8') as f:
                sorted_symbols = filter_symbols(db, predicate=filter_noprimitive, key=sortby_datatypes)
                total,section, = 0,0
                for define in sorted(db.defines.values(), key=lambda d: d.name.lower()):
                    if filtered: continue
                    if True:
                        f.write(define.format_full(namespace=False) + '\n')
                        section += 1
                
                if section: f.write('\n\n')
                total,section, = total+section,0
                for symbol in sorted_symbols:
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.TYPEDEF and not symbol.is_function:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        #f.write('\n')
                        section += 1
                
                if section: f.write('\n\n')
                total,section, = total+section,0
                for symbol in sorted_symbols:
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.TYPEDEF and symbol.is_function:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        #f.write('\n')
                        section += 1
                
                if section: f.write('\n\n')
                total,section, = total+section,0
                for symbol in sorted_symbols:
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.ENUM:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        f.write('\n')
                        section += 1
                
                if section: f.write('\n\n')
                total,section, = total+section,0
                for symbol in sorted_symbols:
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.FLAGS:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        f.write('\n')
                        section += 1
                
                if section: f.write('\n\n')
                total,section, = total+section,0
                for symbol in sorted_symbols:
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.UNION:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        f.write('\n')
                        section += 1
                
                if section: f.write('\n\n')
                total,section, = total+section,0
                for symbol in sorted_symbols:
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.STRUCT:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        f.write('\n')
                        section += 1
                
                #if section: f.write('\n')
                if section or total:
                    f.write('\n\n\n')
                total,section, = total+section,0
                varcount = 0
                for symbol in sorted_symbols:
                    if symbol.kind is ge.SymbolKind.VARIABLE:
                        varcount += 1
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.VARIABLE:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        #f.write('\n')
                        section += 1
                print('total',len([v for v in db.symbols.values() if v.kind == ge.SymbolKind.VARIABLE]),'variables')
                print('found',varcount,'variables')
                print('displayed',section,'variables')
                
                #if section: f.write('\n')
                if section: # or total:
                    f.write('\n\n\n')
                total,section, = total+section,0
                for symbol in sorted_symbols:
                    if is_filtered(symbol): continue
                    if symbol.kind is ge.SymbolKind.FUNCTION:
                        f.write(symbol.format_full(namespace=False) + '\n')
                        #f.write('\n')
                        section += 1
                
                if section: f.write('\n')
                total,section, = total+section,0
                
                f.flush()

    if verbose: print('Done!')

    return 0

#endregion


###########################################################################

del Optional  # cleanup declaration-only imports


## MAIN CONDITION ##

if __name__ == '__main__':
    exit(main())
