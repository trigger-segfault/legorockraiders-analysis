#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Ghidra helper scripts.
"""

__version__ = '0.0.1'
__date__    = '2021-09-30'
__author__  = 'Robert Jordan'

__all__ = ['main']

#######################################################################################

import io, os, re
from struct import *
import traceback
from collections import namedtuple
from struct import Struct
from typing import Optional, Pattern, Tuple


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
    dtparser.add_argument('-A','--assert-size', action='store_true', dest='assert_sizeof', default=False, help='Add size assertions for block datatypes')

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
            # Insert append beteween filename and extension
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
    assert_sizeof = args.assert_sizeof

    #endregion

    ###########################################################################

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
    db.override_legorr_float10_returns()

    # with open()

    # if verbose: print('Formatting header...')
    # try:
    #     data = patch_data(data, new_name=args.dllname, verbose=verbose)
    # except AssertionError as ex:
    #     print('Erroring patching executable, unexpected data found!')
    #     if verbose:
    #         traceback.print_exc()
    #     return 1
    

    sorted_symbols = filter_symbols(db, predicate=filter_noprimitive, key=sortby_datatypes)


    def is_filtered(symbol):
        if filtered:
            if symbol.hide:
                return True
            if symbol.tagged:
                return set(symbol.tagged.tags).intersection(FILTER_TAGS)
        return False
        # if filtered and symbol.hide: continue
    
    def next_section(f, ts:tuple, sectionlines:int=2):
        total,section = ts
        if section and sectionlines: f.write('\n' * sectionlines)

        # sum total with last section, and clear section
        total,section, = total+section,0  

        return total,section



    def write_defines(f, ts:tuple, newlines:int=0, sectionlines:int=2):
        total,section = next_section(f, ts, sectionlines)

        for define in sorted(db.defines.values(), key=lambda d: d.name.lower()):
            if filtered: continue
            if True:  # no filter condition for defines
                f.write(define.format_full(namespace=False) + '\n')
                if newlines: f.write('\n' * newlines)
                section += 1

        return total,section
    
    def write_typedefs(f, ts:tuple, is_function:bool, newlines:int=0, sectionlines:int=2):
        total,section = next_section(f, ts, sectionlines)

        for symbol in sorted_symbols:
            if is_filtered(symbol): continue
            if symbol.kind is ge.SymbolKind.TYPEDEF and (bool(is_function) == bool(symbol.is_function)):
                f.write(symbol.format_full(namespace=False) + '\n')
                if newlines: f.write('\n' * newlines)
                section += 1

        return total,section

    def write_types(f, ts:tuple, kind:ge.SymbolKind, newlines:int=1, sectionlines:int=2):
        total,section = next_section(f, ts, sectionlines)

        for symbol in sorted_symbols:
            if is_filtered(symbol): continue
            if symbol.kind is kind:
                if symbol.kind is ge.SymbolKind.ENUM and symbol.name == 'SurfaceTexture':
                    # HACK: ALways output SurfaceTexture enum as 2-digit hex.
                    f.write(symbol.format_full(namespace=False, assert_sizeof=assert_sizeof, hex_override=2) + '\n')
                else:
                    f.write(symbol.format_full(namespace=False, assert_sizeof=assert_sizeof) + '\n')
                if newlines: f.write('\n' * newlines)
                section += 1

        return total,section

    def write_variables(f, ts:tuple, verbose:bool=False, newlines:int=0, sectionlines:int=3):
        total,section = next_section(f, ts, sectionlines)

        varcount = 0  # total variables, before checking is_filtered
        for symbol in sorted_symbols:
            if symbol.kind is ge.SymbolKind.VARIABLE:
                varcount += 1  # unfiltered variable
            if is_filtered(symbol): continue
            if symbol.kind is ge.SymbolKind.VARIABLE:
                f.write(symbol.format_full(namespace=False) + '\n')
                if newlines: f.write('\n' * newlines)
                section += 1  # filtered variable
        
        if verbose:
            print('total',len([v for v in db.symbols.values() if v.kind == ge.SymbolKind.VARIABLE]),'variables')
            print('found',varcount,'variables')
            print('displayed',section,'variables')

        return total,section
    
    # order:
    #  'D' for funcptr define
    #  'F' for declaration
    #  'd' for commented out funcptr define
    #  'f' for commented out declaration
    def write_functions(f, ts:tuple, order:str='F', newlines:int=0, sectionlines:int=3):
        total,section = next_section(f, ts, sectionlines)

        for symbol in sorted_symbols:
            if is_filtered(symbol): continue
            if symbol.kind is ge.SymbolKind.FUNCTION:
                f.write(symbol.format_address() + '\n')
                for o in order:
                    if o in ('d','f'):
                        f.write('//') # commented out
                    
                    if o in ('D','d'): # funcptr define
                        f.write(symbol.format_define_full(namespace=False, address=False) + '\n')
                    elif o in ('F','f'): # declaration
                        f.write(symbol.format_full(namespace=False, address=False) + '\n')
                if newlines: f.write('\n' * newlines)
                section += 1

        return total,section


    def open_write_subname(subname:str, ext:str=None):
        base,baseext = os.path.splitext(output)
        if ext is None: ext = baseext or ''
        name = f'{base}{subname}{ext}'
        return open(name, 'wt+', encoding='utf-8', newline='\n')


    if output:
        if verbose: print(f'Saving:  {output}')
        if not test:
            with open(output, 'wt+', encoding='utf-8', newline='\n') as f:
                ts = (0,0)  # total,section
                # Define constants
                ts = write_defines(f,ts, 0, 2)
                # Type typedefs
                ts = write_typedefs(f,ts, False, 0, 2)
                # Function typedefs
                ts = write_typedefs(f,ts, True,  0, 2)
                # Normal enums
                ts = write_types(f,ts, ge.SymbolKind.ENUM,   1, 2)
                # Flags enums
                ts = write_types(f,ts, ge.SymbolKind.FLAGS,  1, 2)
                # Unions
                ts = write_types(f,ts, ge.SymbolKind.UNION,  1, 2)
                # Structs
                ts = write_types(f,ts, ge.SymbolKind.STRUCT, 1, 2)
                # Global variables (verbose lists the total number of variables)
                ts = write_variables(f,ts, verbose, 0, 3)
                # Function declarations ('F': Uncommented out, Function declarations)
                ts = write_functions(f,ts, 'F', 0, 3)

                ts = next_section(f,ts, 1)
                f.flush()

                # total,section, = 0,0
                # for define in sorted(db.defines.values(), key=lambda d: d.name.lower()):
                #     if filtered: continue
                #     if True:
                #         f.write(define.format_full(namespace=False) + '\n')
                #         section += 1
                
                # if section: f.write('\n\n')
                # total,section, = total+section,0
                # for symbol in sorted_symbols:
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.TYPEDEF and not symbol.is_function:
                #         f.write(symbol.format_full(namespace=False) + '\n')
                #         #f.write('\n')
                #         section += 1
                
                # if section: f.write('\n\n')
                # total,section, = total+section,0
                # for symbol in sorted_symbols:
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.TYPEDEF and symbol.is_function:
                #         f.write(symbol.format_full(namespace=False) + '\n')
                #         #f.write('\n')
                #         section += 1
                
                # if section: f.write('\n\n')
                # total,section, = total+section,0
                # for symbol in sorted_symbols:
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.ENUM:
                #         if symbol.name == 'SurfaceTexture':
                #             # HACK: ALways output SurfaceTexture enum as 2-digit hex.
                #             f.write(symbol.format_full(namespace=False, assert_sizeof=assert_sizeof, hex_override=2) + '\n')
                #         else:
                #             f.write(symbol.format_full(namespace=False, assert_sizeof=assert_sizeof) + '\n')
                #         f.write('\n')
                #         section += 1
                
                # if section: f.write('\n\n')
                # total,section, = total+section,0
                # for symbol in sorted_symbols:
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.FLAGS:
                #         f.write(symbol.format_full(namespace=False, assert_sizeof=assert_sizeof) + '\n')
                #         f.write('\n')
                #         section += 1
                
                # if section: f.write('\n\n')
                # total,section, = total+section,0
                # for symbol in sorted_symbols:
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.UNION:
                #         f.write(symbol.format_full(namespace=False, assert_sizeof=assert_sizeof) + '\n')
                #         f.write('\n')
                #         section += 1
                
                # if section: f.write('\n\n')
                # total,section, = total+section,0
                # for symbol in sorted_symbols:
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.STRUCT:
                #         f.write(symbol.format_full(namespace=False, assert_sizeof=assert_sizeof) + '\n')
                #         f.write('\n')
                #         section += 1
                
                # #if section: f.write('\n')
                # if section or total:
                #     f.write('\n\n\n')
                # total,section, = total+section,0
                # varcount = 0
                # for symbol in sorted_symbols:
                #     if symbol.kind is ge.SymbolKind.VARIABLE:
                #         varcount += 1
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.VARIABLE:
                #         f.write(symbol.format_full(namespace=False) + '\n')
                #         #f.write('\n')
                #         section += 1
                # print('total',len([v for v in db.symbols.values() if v.kind == ge.SymbolKind.VARIABLE]),'variables')
                # print('found',varcount,'variables')
                # print('displayed',section,'variables')
                
                # #if section: f.write('\n')
                # if section: # or total:
                #     f.write('\n\n\n')
                # total,section, = total+section,0
                # for symbol in sorted_symbols:
                #     if is_filtered(symbol): continue
                #     if symbol.kind is ge.SymbolKind.FUNCTION:
                #         f.write(symbol.format_full(namespace=False) + '\n')
                #         #f.write('\n')
                #         section += 1
                
                # if section: f.write('\n')
                # total,section, = total+section,0
                
                # f.flush()
            
            ############################################
            

            # type typedefs, enums, flags, unions, structs
            with open_write_subname('.datatypes', '.h') as f:
                f.write('#pragma once' + '\n')
                f.write('//' + '#include "functypes.h"' + '\n')
                f.write('\n\n\n')
                ts = (0,0)  # total,section
                # Type typedefs
                ts = write_typedefs(f,ts, False, 0, 2)
                # Normal enums
                ts = write_types(f,ts, ge.SymbolKind.ENUM,   1, 2)
                # Flags enums
                ts = write_types(f,ts, ge.SymbolKind.FLAGS,  1, 2)
                # Unions
                ts = write_types(f,ts, ge.SymbolKind.UNION,  1, 2)
                # Structs
                ts = write_types(f,ts, ge.SymbolKind.STRUCT, 1, 2)

                ts = next_section(f,ts, 1)
                f.flush()
            
            # function typedefs
            with open_write_subname('.functypes', '.h') as f:
                f.write('#pragma once' + '\n')
                f.write('#include "datatypes.h"' + '\n')
                f.write('\n\n\n')
                ts = (0,0)  # total,section
                # Function typedefs
                ts = write_typedefs(f,ts, True,  0)

                ts = next_section(f,ts, 1)
                f.flush()
            
            # global variables
            with open_write_subname('.globals_unfiltered', '.h') as f:
                f.write('#pragma once' + '\n')
                f.write('#include "datatypes.h"' + '\n')
                f.write('#include "functypes.h"' + '\n')
                f.write('\n\n\n')
                ts = (0,0)  # total,section
                # Global variables (not verbose)
                ts = write_variables(f,ts, False, 0)

                ts = next_section(f,ts, 1)
                f.flush()
            
            # function declarations
            with open_write_subname('.source', '.h') as f:
                f.write('#pragma once' + '\n')
                f.write('#include "datatypes.h"' + '\n')
                f.write('#include "functypes.h"' + '\n')
                f.write('\n')
                f.write('//00400000' + '\n')
                f.write('\n\n')
                ts = (0,0)  # total,section
                # Function declarations ('F': Uncommented out, Function declarations)
                ts = write_functions(f,ts, 'F', 0)

                ts = next_section(f,ts, 1)
                f.flush()
            
            ############################################

            # HACK: Use this as the anchor which splits
            #        datatypes_unfiltered from source_unfiltered.
            DATA_TO_SOURCE_ANCHOR = '\n\n\n\n\n'
            # HACK: Backup anchor if the above never had datatypes emitted.
            DATA_TO_SOURCE_ANCHOR_2 = 'void __cdecl'

            #source_h, datatypes_h = None, None
            with open(inputs[0], 'rt', encoding='utf-8') as f:
                # source.h is exported with 4 spaces per indent
                source_h = ge.sub_crlf2lf(ge.sub_spaces4tabs(f.read()))
                dt_idx = source_h.find(DATA_TO_SOURCE_ANCHOR)
                if dt_idx == -1:
                    print('Failed to find newlines match in source.h')
                    dt_idx = source_h.find(DATA_TO_SOURCE_ANCHOR_2)
                if dt_idx == -1:
                    print('Failed to find __cdecl match in source.h')
                    # Failed, don't both writing these files
                    source_h, datatypes_h = None, None
                else:
                    # Split first occurrence and strip whitespace around each section
                    datatypes_h = source_h[:dt_idx].strip()
                    source_h    = source_h[dt_idx:].strip()
                    #source_h, datatypes_h = [s.strip() for s in source_h.split(dt_idx, 1)]

                
            # type typedefs, enums, flags, unions, structs
            if datatypes_h:
                with open_write_subname('.datatypes_unfiltered', '.h') as f:
                    f.write('#pragma once' + '\n')
                    f.write('\n\n\n')

                    f.write(datatypes_h)

                    del datatypes_h  # cleanup memory

                    f.write('\n\n')
                    f.flush()
            
            # function declarations (unfiltered)
            if source_h:
                with open_write_subname('.source_unfiltered', '.h') as f:
                    f.write('#pragma once' + '\n')
                    f.write('#include "datatypes_unfiltered.h"' + '\n')
                    f.write('\n\n\n')
                    
                    f.write(source_h)

                    del source_h  # cleanup memory

                    f.write('\n\n')
                    f.flush()
            
            filename_c = os.path.splitext(inputs[0])[0] + '.c'
            if os.path.isfile(filename_c):
                with open(filename_c, 'rt', encoding='utf-8') as f:
                    # source.c is exported with 2 spaces per indent
                    source_c = ge.sub_crlf2lf(ge.sub_spaces2tabs(f.read()))
                    # We want to strip the default #include file and write our own.
                    inc_idx = source_c.find('\n')
                    if inc_idx == -1:
                        print('Failed to find include newline match in source.c')
                        # Failed, don't both writing these files
                        source_c = None
                    else:
                        # Trim out the first #include file line, and replace pointless
                        #  empty lines between function signatures and their body
                        source_c =  re.compile(r"\)\n\n\{").sub(')\n{', source_c[inc_idx:].strip())
            else:
                # Failed, don't both writing this file
                print(f'Failed to find {filename_c}\nNo source.c file will be built.')
                source_c = None
            
            # C source file
            if source_c:
                with open_write_subname('.source', '.c') as f:
                    f.write('#include "datatypes_unfiltered.h"' + '\n')
                    f.write('#include "globals_unfiltered.h"' + '\n')
                    f.write('#include "source_unfiltered.h"' + '\n')
                    f.write('\n\n\n')

                    f.write(source_c)

                    del source_c  # cleanup memory

                    f.write('\n\n\n')
                    f.flush()
            
            ############################################
            
            # declare FUNC
            with open_write_subname('.openlrr.functions', '.h') as f:
                ts = (0,0)
                write_functions(f, ts, 'F', 1, 0)
                f.flush()
            
            # define FUNC_PTR
            with open_write_subname('.openlrr.defines', '.h') as f:
                ts = (0,0)
                write_functions(f, ts, 'D', 1, 0)
                f.flush()
            
            # define FUNC_PTR
            # //declare FUNC
            with open_write_subname('.openlrr.combined1', '.h') as f:
                ts = (0,0)
                write_functions(f, ts, 'Df', 1, 0)
                f.flush()
            
            # //define FUNC_PTR
            # declare FUNC
            with open_write_subname('.openlrr.combined2', '.h') as f:
                ts = (0,0)
                write_functions(f, ts, 'dF', 1, 0)
                f.flush()

    if verbose: print('Done!')

    return 0

#endregion


###########################################################################

del Optional  # cleanup declaration-only imports


## MAIN CONDITION ##

if __name__ == '__main__':
    exit(main())
