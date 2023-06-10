
import os, re
from typing import Dict, List, Optional, Tuple
from collections import namedtuple

DEFAULT_NAMESPACE = 'LegoRR'

RE_FUNCADDR = re.compile(r"""
^\/\/[ ]<LegoRR\.exe[ ]@(?P<address>[0-9A-Fa-f]{8})>\n # Function address
(\/\/[^\n]*\n)* # Skip comments / commented out defines before function declaration
[^\n]*?[ ]__cdecl[ ](?P<name>[A-Za-z_][A-Za-z_0-9]*)\( # Function name
""", re.VERBOSE | re.MULTILINE)

FunctionAddr = namedtuple('FunctionAddr', ('address', 'name'))


def find_functions(text:str) -> List[FunctionAddr]:
    funcs = [] # type: list[FunctionAddr]
    matches = list(RE_FUNCADDR.finditer(text))
    print(f'len(matches) = {len(matches)}')
    print(f'count("__cdecl") = {text.count("__cdecl")}')
    #
    for m in matches:
        # print(type(m))
        # print(m)
        # print(dir(m))
        funcs.append(FunctionAddr(int(m['address'], 16), m['name']))
    #
    return funcs

def hook_functions(funcs:List[FunctionAddr], module:str, namespace:Optional[str]):
    namespaceSyntax = f'{namespace}::' if namespace else ''
    namespacePart = f'{namespace}_' if namespace else ''
    print(f'bool interop_hook_{namespacePart}{module}(void)')
    print('{')
    print('\tbool result = true;')
    print()
    for func in funcs:
        print(f'\tresult &= hook_write_jmpret(0x{func.address:08x}, {namespaceSyntax}{func.name});')
    print()
    print('\treturn_interop(result);')
    print('}')



def main(args:list=None):
    if args is None:
        import sys
        args = sys.argv[1:]
    #
    filepath = args[0]
    namespace = DEFAULT_NAMESPACE
    if len(args) >= 2:
        namespace = args[1]
    #
    with open(filepath, 'rt', encoding='utf-8') as f:
        funcs = find_functions(f.read())
    #
    module = os.path.splitext(os.path.basename(filepath))[0]
    hook_functions(funcs, module, namespace)
    #
    return 0


if __name__ == '__main__':
    exit(main())
