#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Take OpenLRR function address defines and create commented-out function declarations below them.
"""

__version__ = '0.0.1'
__date__    = '2023-06-10'
__author__  = 'Robert Jordan'

__all__ = ['main']

#######################################################################################

import re
from typing import Match, Optional, Pattern, Tuple


#######################################################################################

PAT_FUNCDEFINE:str = r"""
(?P<comment>\/\/[ \t]*<LegoRR\.exe[ \t]*@[A-Fa-f0-9]{8}>)\n # Function location comment
\#define[ \t]+(?P<name>[A-Za-z_][A-Za-z_0-9]*)[ \t]* # define keyword and function name
\(\(
    (?P<return>[^()]+?)[ \t]* # Return value
    \([ \t]*?(?P<call>__[a-z_]+)[ \t]*?\*[ \t]*\)[ \t]*? # Calling convention
    (?P<args>\((?:[^()]|\([^()]*\))*\)) # Function arguments
\)0x[A-Fa-f0-9]{8}\)[ \t]*
"""

RE_FUNCDEFINE_ALLOWDECL:Pattern = re.compile(rf"""
{PAT_FUNCDEFINE} # Find function address define
""", re.VERBOSE | re.MULTILINE)

RE_FUNCDEFINE_NODECL:Pattern = re.compile(rf"""
{PAT_FUNCDEFINE} # Find function address define
(?!\n\/\/) # Skip lines that already have a commented out function definition below them
""", re.VERBOSE | re.MULTILINE)


#######################################################################################

# Create a string that declares a function from a given define match.
def create_function(m:Match, definition:bool=False) -> str:
    return_type = m['return'].strip()
    calling_conv = m['call'].strip()
    name = m['name'].strip()
    args = m['args'].strip()
    namespace = 'LegoRR::' if definition else ''
    comment = (m['comment'] + '\n') if definition else ''
    return f'{comment}//{return_type} {calling_conv} {namespace}{name}{args};'

# Add declarations below all matched defines for a header file.
def add_declarations(text:str, verbose:bool=False) -> str:
    m = RE_FUNCDEFINE_NODECL.search(text)
    while m is not None:
        end = m.end()
        decl = f'\n{create_function(m, definition=False)}' # Add declaration on a new line, commented out.
        if verbose:
            print(f'{text[m.start():end]}{decl}\n')
        text = f'{text[:end]}{decl}{text[end:]}'
        m = RE_FUNCDEFINE_NODECL.search(text, end + len(decl))
    return text

# Create definitions based on matched defines for a cpp file.
def make_definitions(text:str, verbose:bool=False) -> str:
    out_text = ''
    m = RE_FUNCDEFINE_ALLOWDECL.search(text)
    while m is not None:
        end = m.end()
        decl = f'{create_function(m, definition=True)}' # Add definition, commented out.
        if verbose:
            print(f'{decl}\n')
        out_text += f'{decl}\n\n'
        m = RE_FUNCDEFINE_ALLOWDECL.search(text, end)
    return out_text

# Returns the (total function defines, function defines without declarations).
def count_defines(text:str) -> Tuple[int, int]:
    total = len(RE_FUNCDEFINE_ALLOWDECL.findall(text))
    nodecl = len(RE_FUNCDEFINE_NODECL.findall(text))
    return (total, nodecl)


#######################################################################################

#region ## MAIN FUNCTION ##

def main(argv:Optional[list]=None) -> int:
    import os

    #region ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='OpenLRR function declaration builder',
        add_help=True)

    parser.add_argument('input', metavar='FILE', help='header file to read and add function declarations to')
    parser.add_argument('-d', '--definitions', metavar='FILE', dest='definitions', default=None, required=False, help='optional output file for function definitions')

    parser.add_argument('-q', '--quiet', action='store_true', default=False, help='don\'t print actions being performed')
    parser.add_argument('-T', '--test', action='store_true', default=False, help='test program without saving any changes')

    #endregion

    ###########################################################################

    #region ## PARSER VALIDATION ##

    args = parser.parse_args(argv)

    verbose = not args.quiet

    #endregion

    ###########################################################################

    # Read file with defines.
    with open(args.input, 'rt', encoding='utf-8') as f:
        text = f.read()
    
    total, nodecl = count_defines(text)
    new_text = add_declarations(text, verbose=verbose)
    print(f'{nodecl} functions added. {(total-nodecl)} functions already have declarations.')

    # Write back to header file.
    if text == new_text:
        print('No declarations were made.')
        #print(f'{total} functions added. {(total-nodecl)} functions already have declarations.')
        #print('Either no defines were found, or all existing defines already had a function declaration after it.')
    elif not args.test:
        with open(args.input, 'wt+', encoding='utf-8') as f:
                f.write(new_text)
                f.flush()

    # Optionally write file with definitions.
    if args.definitions is not None:
        cpp_text = make_definitions(text, verbose=verbose)
        if not cpp_text: # Only write a new file if definitions were created.
            print('No definitions were made.')
        elif not args.test:
            with open(args.definitions, 'wt+', encoding='utf-8') as f:
                f.write(cpp_text)
                f.flush()

    return 0


#endregion


###########################################################################

del Optional  # cleanup declaration-only imports


## MAIN CONDITION ##

if __name__ == '__main__':
    exit(main())
