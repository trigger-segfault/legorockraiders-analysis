#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""File and I/O utility and helper functions.
"""

__version__ = '0.1.0'
__date__    = '2021-06-08'
__author__  = 'Robert Jordan'

__all__ = ['check_header', 'get_linker_time']

#######################################################################################

import io
from datetime import datetime, timezone
from typing import Optional, Set, Union
from .common import UINT32


#######################################################################################

#region ## FILE HELPERS ##

def get_linker_time(file:Union[str,bytes,io.BufferedReader], tz:Optional[timezone]=None) -> datetime:
    """get_linker_time(filename) -> datetime or build
    
    source: <https://stackoverflow.com/a/1600990/7517185>
    """
    if isinstance(file, str):
        with open(file, 'rb') as f:
            file = f.read(2048)
    elif not isinstance(file, (bytes,bytearray)):
        file = file.read(2048)
    
    # c_PeHeaderOffset = 60
    # c_LinkerTimestampOffset = 8
    offset = UINT32.unpack_from(file, 60)[0]  # c_PeHeaderOffset
    timestamp = UINT32.unpack_from(file, offset + 8)[0]  # offset + c_LinkerTimestampOffset
    return datetime.fromtimestamp(timestamp, timezone.utc if tz is None else tz)


def check_header(file:Union[str,bytes,io.BufferedReader], signatures:Set[bytes], peek:bool=False) -> bool:
    """check_header('program.exe', {b'MZ'}) -> bool
    check_header(filebytes, signatures) -> bool
    check_header(filelike, signatures, peek=True) -> bool
    
    Check the current file position for signature byte patterns.
    Use peek to maintain the file position (if supported).
    """
    if not signatures: raise ValueError('check_header() requires at least one signature argument')
    max_len = max(len(s) for s in signatures)
    
    if isinstance(file, str):  # filepath
        with open(file, 'rb') as f:
            filesig = f.read(max_len)
            #return check_header(f, signatures, peek=False)
        
    elif isinstance(file, (bytes,bytearray)):  # bytes data
        filesig = file
        
    else:  # file-like
        filesig = b''
        if hasattr(file, 'peek'):
            filesig = file.peek(max_len) #[:max_len]
        if len(filesig) < max_len:
            # peek() doesn't exist or didn't give total needed bytes, fallback to read()
            filesig = file.read(max_len)
            if peek and filesig and file.seekable():
                file.seek(-len(filesig), 1)  # go back to initial position
    
    return any(filesig.startswith(s) for s in signatures)

#endregion

#######################################################################################

del io, Optional, Set, Union  # cleanup declaration-only imports
