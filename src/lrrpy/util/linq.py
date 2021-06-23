#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Type-casting and ensuring functions
"""

__version__ = '0.1.1'
__date__    = '2021-09-19'
__author__  = 'Robert Jordan'

__all__ = ['ordered_unique', 'list_to_bytes', 'list_to_str', 'letterset']

#######################################################################################

from collections import OrderedDict
from typing import Any, Dict, Iterable, List, TypeVar, Union

from .typecast import to_str, to_bytes


#######################################################################################

#region ## UTILITIES AND HELPERS ##

T = TypeVar('T')
# exclude remaining duplicates while maintaining order
def ordered_unique(items:Iterable[T]) -> Iterable[T]:
    d = OrderedDict()  # Dict[T, Any]
    for item in items:
        d.setdefault(item, None)
    return d.keys()
    

def list_to_bytes(items:Iterable[Union[str,bytes]]) -> List[bytes]:
    return [to_bytes(s) for s in items]

def list_to_str(items:Iterable[Union[str,bytes]]) -> List[str]:
    return [to_str(s) for s in items]

# def has_alpha(s:str) -> bool: return any(c.isalpha() for c in s)
# def has_alnum(s:str) -> bool: return any(c.isalnum() for c in s)
# def has_digit(s:str) -> bool: return any(c.isdigit() for c in s)
# def has_lower(s:str) -> bool: return any(c.islower() for c in s)
# def has_upper(s:str) -> bool: return any(c.isupper() for c in s)


def letterset(text:Union[str,bytes,Iterable[str],Iterable[bytes]]) -> Union[str,bytes]:
    """letterset('Hello world') -> ' Hdelorw'
    letterset([str1, str2, str3]) -> letterset(str1 + str2 + str3)
    """
    if isinstance(text, (str,bytes,bytearray)): # single (str,bytes,bytearray)
        unique = set(text)
    else:  # iterable of (str,bytes,bytearray)
        from itertools import chain
        text, texts = text[0], text  # text[0] is used to check the type (str|bytes) passed in
        unique = set(chain.from_iterable(texts))
    if isinstance(text, (bytes,bytearray)):
        return b''.join(sorted(unique))
    else:
        return ''.join(sorted(unique))

#endregion


#######################################################################################

del Any, Dict, Iterable, List, TypeVar, Union  # cleanup declaration-only imports
