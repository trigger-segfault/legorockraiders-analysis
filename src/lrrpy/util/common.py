#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Common utilities
"""

__version__ = '0.0.1'
__date__    = '2021-06-19'
__author__  = 'Robert Jordan'

__all__ = ['TEXT_CODEC', 'cstring']

#######################################################################################

import codecs
from struct import Struct
from typing import Optional, Tuple, Union


#######################################################################################

#region ## TEXT ENCODING ##

TEXT_ENCODING:str = 'ascii'
TEXT_CODEC:codecs.CodecInfo = codecs.lookup(TEXT_ENCODING)

def cstring(data:bytes, offset:Optional[int]=None) -> Tuple[str, int]:
    """cstring(bytes) -> (str, bytes read)
    
    Return length includes the null-terminator
    """
    end = data.index(0, offset)
    return (data[offset:end].decode(), end+1 - offset)

#endregion

#######################################################################################

#region ## BASIC STRUCT TYPES ##

SINT8 = Struct('<b')
UINT8 = Struct('<B')
SINT16 = Struct('<h')
UINT16 = Struct('<H')
SINT32 = Struct('<i')
UINT32 = Struct('<I')
SINT64 = Struct('<q')
UINT64 = Struct('<Q')
REAL32 = Struct('<f')

#endregion

#region ## LRR STRUCT TYPES ##

S4_UINT32 = Struct('<4sI')
UINT32_4 = Struct('<IIII')

# X32_UINT32 = Struct('<4xI')
# X32_UINT32_2 = Struct('<4xII')
# X64_UINT32_2 = Struct('<8xII')

# UINT32_2 = Struct('<II')
# UINT32_3 = Struct('<III')
# # UINT32_2_SINT16 = Struct('<IIh')
# UINT16_UINT32_SINT16 = Struct('<HIh')
# UINT16_SINT32 = Struct('<Hi')
# UINT16_UINT32 = Struct('<HI')
# UINT16_2 = Struct('<HH')
# UINT16_REAL32 = Struct('<Hf')
# UINT16_UINT32_2_UINT16 = Struct('<HIIH')
# UINT16_UINT32_UINT16 = Struct('<HIH')

# UINT16_2_UINT32_SINT16 = Struct('<HHIh')
# UINT16_UINT32_X16 = Struct('<HI2x')

# UINT32_UINT16 = Struct('<IH')
# UINT64_UINT32_2 = Struct('<QII')
# S16_UINT32_3 = Struct('<16sIII')

# UINT32_X32_UINT16 = Struct('<I4xH')
# UINT32_2_UINT16 = Struct('<I4xH')

#endregion

#######################################################################################

#region ## DISABLE ITER FUNCTIONS ##

def _tupleno__len__(self) -> None: raise TypeError(f'object of type {self.__class__.__name__!r} has no len()')
def _tupleno__iter__(self) -> None: raise TypeError(f'{self.__class__.__name__!r} object is not iterable')
def _tupleno__getitem__(self, key) -> None: raise TypeError(f'{self.__class__.__name__} object is not subscriptable')
def _tupleno__contains__(self, key) -> None: raise TypeError(f'argument of type {self.__class__.__name__} is not iterable')
def _tuplenoindex(self, value, start=None, stop=None) -> None: raise TypeError('{self.__class__.__name__}.index() not supported')
def _tuplenocount(self, value, start=None, stop=None) -> None: raise TypeError('{self.__class__.__name__}.count() not supported')

# # __len__, __iter__, __getitem__, __contains__ = _tupleno__len__, _tupleno__iter__, _tupleno__getitem__, _tupleno__contains__
# # index, count = _tuplenoindex, _tuplenocount
# __len__ = _tupleno__len__
# # __iter__ = _tupleno__iter__
# # __getitem__ = _tupleno__getitem__
# # __contains__ = _tupleno__contains__
# # index = _tuplenoindex
# # count = _tuplenocount

#endregion

#######################################################################################

del Optional, Tuple, Union  # cleanup declaration-only imports
