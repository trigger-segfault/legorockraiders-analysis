#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""String table to C/C++ enum builder.
"""

__version__ = '0.0.1'
__date__    = '2021-07-17'
__author__  = 'Robert Jordan'

__all__ = ['table2enum']

#######################################################################################

from collections import namedtuple
import io, os, re
# from struct import pack, unpack, unpack_from, pack_into, iter_unpack
from typing import Callable, List, Optional, Union


#######################################################################################

#region Conversion Shorthands
upr, lwr, tit, cap = str.upper, str.lower, str.title, str.capitalize
#endregion

#region Indent Constants
TAB:str    = '\t'
SPACE1:str = ' '
SPACE2:str = '  '
SPACE3:str = '   '
SPACE4:str = '    '
#endregion

#######################################################################################

## source: <https://stackoverflow.com/a/29920015/7517185>
# def camel_case_split(name:str, conv2=str) -> list:
def camelSplit(name:str, conv2:Callable[[str],str]=str) -> List[str]:
    matches = re.finditer(r'.+?(?:(?<=[a-z])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])|$)', name)
    return [conv2(m.group(0)) for m in matches]

def camel(join:str='', conv:Callable[[str],str]=str) -> Callable[[str],str]:
    def boundCamelSplit(name:str, joinchr:str=join, conv2=conv) -> List[str]:
        return joinchr.join(camelSplit(name, conv2))
    return boundCamelSplit

# def camelSplit(name, conv2=str) -> str:

# PTLEvent.KEYS.update([(pe.key,pe) for pe in (PTLEvent(n,i) for i,n in enumerate(PTLEvent.PTL_NAMES))])

def find_maxlen(strings:List[Optional[str]]) -> int:
    return max(len(s) for s in strings if s is not None)

def prepare_names(strings:List[Optional[str]], prefix:Optional[str]=None, lstrip:Optional[str]=None, conv:Optional[Callable[[str],str]]=None, *, require_strip:bool=True) -> List[Optional[str]]:
    if strings is None:
        raise TypeError('strings cannot be None')
    if lstrip is None:
        lstrip = ''
    elif not isinstance(lstrip, str):
        raise TypeError(f'lstrip must be str or NoneType, not {lstrip.__class__.__name__}')
    if prefix is None:
        prefix = ''
    elif not isinstance(prefix, str):
        raise TypeError(f'prefix must be str or NoneType, not {prefix.__class__.__name__}')
    if conv is None:
        conv = str
    elif not callable(conv):
        raise TypeError(f'conv must be callable or NoneType, not {conv.__class__.__name__}')
    #
    names = list(strings)
    for i in range(len(names)):
        name = names[i]
        if name is not None:
            if name.startswith(lstrip):
                name = name[len(lstrip):]
            elif require_strip:
                raise ValueError(f'strings[{i}] {name!r} does not start with lstrip prefix {lstrip!r}')
            names[i] = f'{prefix}{conv(name)}'
    #
    return names

# def build_cenum(names:List[Optional[str]], enumname:str, prefix:str=None, lstrip:str='', conv:Callable[[str],str]=str.upper, indent:str='\t', pad:bool=True, number:str=str) -> str:

def build_cenum(enumname:str, strings:List[Optional[str]], prefix:str=None, lstrip:str='', conv:Callable[[str],str]=str.upper, indent:str='\t', pad:bool=True, number:Optional[Callable[[int],str]]=str, *, require_strip:bool=True, enumtype:Optional[str]=None):
    # if lstrip is None:
    #     lstrip = 0
    # elif isinstance(lstrip, str):
    #     lstrip = len(lstrip)
    #
    if number is None:
        pad = False
    elif isinstance(number, str):
        formatNumberStr = number
        def formatNumber(value):
            return formatNumberStr.format(value)
        number = formatNumber
    elif not callable(number):
        raise TypeError(f'number must be callable or NoneType, not {number.__class__.__name__}')
    #
    names = prepare_names(strings, prefix, lstrip, conv, require_strip=require_strip)
    maxlen = find_maxlen(names)
    if pad:
        maxlen = find_maxlen(names)
        padnames = [(s.ljust(maxlen) if s is not None else None) for s in names]
    else:
        padnames = names
    #
    writer = io.StringIO()
    writer.write(f'\nenum {enumname}')
    if enumtype is not None:
        writer.write(f' : {enumtype}')
    writer.write('\n{')
    #
    for i,name in enumerate(padnames):
        if name is not None:
            writer.write(f'\n{indent}{name}')
            if number is not None:
                writer.write(f' = {number(i)}')
            writer.write(',')
    #
    writer.write('\n};\n')
    writer.flush()
    return writer.getvalue()

# keysenum = build_cenum('Keys', g_KEYS_TABLE, None, None, str, '\t', True, str, enumtype='int')
# print(keysenum)

# def writetext(filename:str, text:str) -> int:
#     with open(filename, 'wt+') as writer:
#         result = writer.write(text)
#         writer.flush()
#         return result

# with open('')


    # text = f'\n\nenum {enumname}\n{{\n'
    # names2 = [conv(n[lstrip:]) for n in names]
    # if pad:
    #     maxlen = max(len(n) for n in names2)
    #     names2 = [n.ljust(maxlen) for n in names2]
    # for i,name in enumerate(names2):
    #     text += f'{indent}{prefix}{name} = {i},\n'
    # text += f'}};\n\n'
    # with open(file, 'wt+', encoding='utf-8') as f:
    #     f.write(text)
    #     f.flush()
    # # for name in names:
    # #     n = conv(name[strippre:])
    # #     text += f'{indent}{n} = '
