#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Type-casting and ensuring functions
"""

__version__ = '0.1.1'
__date__    = '2021-06-19'
__author__  = 'Robert Jordan'

__all__ = ['TEXT_CODEC', 'to_bytes', 'to_str', 'to_float', 'signed_b', 'signed_h', 'signed_i', 'signed_q', 'unsigned_B', 'unsigned_H', 'unsigned_I', 'unsigned_Q']

#######################################################################################

from typing import Union
from .common import TEXT_CODEC


#######################################################################################

#region ## STRING / BYTES HELPERS ##

def to_bytes(text:Union[bytes,str], *, _enc=TEXT_CODEC.encode) -> bytes:
    """to_bytes(bytes) -> bytes
    to_bytes(str) -> str.encode('ascii')

    helper function to allow passing bytes or str.
    """
    return _enc(text)[0] if isinstance(text, str) else text

def to_str(text:Union[str,bytes], *, _dec=TEXT_CODEC.decode) -> str:
    """to_str(str) -> str
    to_str(bytes) -> bytes.decode('ascii')

    helper function to allow passing str or bytes.
    """
    return _dec(text)[0] if isinstance(text, bytes) else text

#endregion

#region ## FLOAT HELPERS ##

def to_float(num:Union[float,int]) -> float:
    """to_float(float) -> float
    to_float(int) -> float(int)

    helper function to allow passing float or int.
    """
    return float(num) if isinstance(num, int) else num

#endregion

#region ## INT SIGNEDNESS HELPERS ##

## source: <https://stackoverflow.com/a/37095855/7517185>

def unsigned_B(num:int) -> int:
    """Returns unsigned value of signed (or unsigned) 8-bit integer (struct fmt 'B')
    """
    return num & 0xff

def signed_b(num:int) -> int:
    """Returns signed value of unsigned (or signed) 8-bit integer (struct fmt 'b')
    """
    return ((num & 0xff) ^ 0x80) - 0x80

def unsigned_H(num:int) -> int:
    """Returns unsigned value of signed (or unsigned) 16-bit integer (struct fmt 'H')
    """
    return num & 0xffff

def signed_h(num:int) -> int:
    """Returns signed value of unsigned (or signed) 16-bit integer (struct fmt 'h')
    """
    return ((num & 0xffff) ^ 0x8000) - 0x8000

def unsigned_I(num:int) -> int:
    """Returns unsigned value of signed (or unsigned) 32-bit integer (struct fmt 'I')
    """
    return num & 0xffffffff

def signed_i(num:int) -> int:
    """Returns signed value of unsigned (or signed) 32-bit integer (struct fmt 'i')
    """
    return ((num & 0xffffffff) ^ 0x80000000) - 0x80000000

def unsigned_Q(num:int) -> int:
    """Returns unsigned value of signed (or unsigned) 64-bit integer (struct fmt 'Q')
    """
    return num & 0xffffffffffffffff

def signed_q(num:int) -> int:
    """Returns signed value of unsigned (or signed) 64-bit integer (struct fmt 'q')
    """
    return ((num & 0xffffffffffffffff) ^ 0x8000000000000000) - 0x8000000000000000

#endregion


#######################################################################################

del Union  # cleanup declaration-only imports
