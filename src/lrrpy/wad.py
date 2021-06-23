#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""WAD file reader
"""

__version__ = '0.0.1'
__date__    = '2021-06-19'
__author__  = 'Robert Jordan'

__all__ = ['WAD', 'WADEntry']

#######################################################################################

from collections import namedtuple
import io, os
from typing import Any, Dict, Iterator, List, Optional, Tuple, Union

from .util.file import check_header
from .util.common import TEXT_CODEC, S4_UINT32, UINT32_4
from .util.common import _tupleno__len__, _tupleno__iter__, _tupleno__getitem__, _tupleno__contains__, _tuplenoindex, _tuplenocount


#######################################################################################

class WADEntry(namedtuple('_WADEntry', ('path', 'origpath', 'version', 'size', 'size2', 'offset', 'wad'))):
    #__slots__ = ('path', 'origpath', 'version', 'size', 'size2', 'offset', 'wad')
    path:str
    origpath:str
    version:int
    size:int
    size2:int
    offset:int
    wad:Optional['WAD']

    # def __init__(self, path:str, origpath:str, version:int, size:int, size2:int, offset:int, wad:Optional['WAD']=None):
    #     self.path = path
    #     self.origpath = origpath
    #     self.version = version
    #     self.size = size
    #     self.size2 = size2
    #     self.offset = offset
    #     self.wad = wad
    
    @property
    def end_offset(self) -> int:
        return self.offset + self.size
    @property
    def name(self, *, _basename=os.path.basename) -> str:
        return _basename(self.path)
    @property
    def dirname(self, *, _dirname=os.path.dirname) -> str:
        return _dirname(self.path)
    @property
    def ext(self, *, _splitext=os.path.splitext) -> str:
        return _splitext(self.path)[0].lower()
    @property
    def wadpath(self, *, _join=os.path.join) -> str:
        return _join(self.wad.path, self.path)
    @property
    def wadnamepath(self, *, _basename=os.path.basename, _join=os.path.join) -> str:
        return _join(_basename(self.wad.path), self.path)
    
    def __repr__(self) -> str:
        vername = '' if self.version == 1 else f' [v{self.version}]'
        return f'<{self.__class__.__name__}: {self.path!r} off={self.offset} size={self.size}{vername}>'
        # return f'<{self.__class__.__name__}: path={self.path!r} off={self.offset} size={self.size} size2={self.size2} [v{self.version}]>'
    __str__ = __repr__
    
    #region ## DISABLE ITER FUNCTIONS ##
    # __len__, __iter__, __getitem__, __contains__ = _tupleno__len__, _tupleno__iter__, _tupleno__getitem__, _tupleno__contains__
    index, count = _tuplenoindex, _tuplenocount
    __len__, __iter__ = _tupleno__len__, _tupleno__iter__
    #endregion

class WAD:
    """WAD(filename) -> parsed wad file and entries

    source: <https://kb.rockraidersunited.com/WAD_file>
    """
    __slots__ = ('path', 'mode', 'fp', 'data', 'path_end', 'orig_end', 'ent_end', 'entries', 'lookup')
    path:str
    mode:str
    fp:io.BufferedReader
    data:bytes
    path_end:int
    orig_end:int  # absolute offset in the file
    ent_end:int
    entries:List[WADEntry]
    lookup:Dict[str,WADEntry]

    SIGNATURES:Dict[bytes,Tuple[int,bool]] = {
        b'WWAD': (0, False), # version 0, decrypted
    }

    def __init__(self, path:str, mode:str='r'):
        self.path = path
        self.mode = mode
        self.fp = None
        with open(path, 'rb') as fp:
            data, path_end, orig_end, ent_end, entries = self._parse(fp, self)
        
        lookup = {}
        for i,ent in enumerate(entries):
            entpath = ent.path
            existing = lookup.setdefault(self._normpath(entpath), ent)
            if existing is not ent:
                i2 = entries.index(existing)
                print(f'duplicate entry path {entpath!r}, index: [{i}], orig index: {i2}')
        
        self.data = data
        self.path_end = path_end
        self.orig_end = orig_end
        self.ent_end = ent_end
        self.entries = entries
        self.lookup = lookup
        # self.fp = open(path, 'rb')
    
    @classmethod
    def check(cls, file:Union[str,bytes,io.BufferedReader], peek:bool=False) -> bool:
        return check_header(file, cls.SIGNATURES, peek=peek)
    
    @property
    def name(self, *, _basename=os.path.basename) -> str:
        return _basename(self.path)
    @property
    def dirname(self, *, _dirname=os.path.dirname) -> str:
        return _dirname(self.path)
    @property
    def ext(self, *, _splitext=os.path.splitext) -> str:
        return _splitext(self.path)[0].lower()
    
    def __repr__(self) -> str:
        return f'<{self.__class__.__name__}: {self.name!r} entries={len(self.entries)}>'
    __str__ = __repr__
    
    def __len__(self) -> int:
        return len(self.entries)
    def __iter__(self) -> Iterator[WADEntry]:
        return iter(self.entries)
    def __contains__(self, entry:Union[str,WADEntry]) -> bool:
        if isinstance(entry, str):
            return self._normpath(entry) in self.lookup
        return entry in self.entries
    def __getitem__(self, key:Union[str,int,slice]) -> WADEntry:
        if isinstance(key, str):
            return self.lookup[self._normpath(key)]
        return self.entries[key]

    def get(self, key:str, default:Any=None) -> Optional[WADEntry]:
        return self.lookup.get(key, default)
    
    @staticmethod
    def _normpath(path:str) -> str:
        return path.lower().replace('/','\\')

    @classmethod
    def _parse(cls, reader:io.BufferedReader, wad:Optional['WAD']=None, *, _s4_u32=S4_UINT32.unpack_from, _u32_4=UINT32_4.unpack_from, _dec=TEXT_CODEC.decode, _Ent=WADEntry) -> Tuple[bytes, int, int, int, List[WADEntry]]:
        data = reader.read()
        signature, count = _s4_u32(data, 0)
        assert(signature in cls.SIGNATURES)

        path_dirs = [None] * count
        orig_dirs = [None] * count
        entries  = [None] * count

        hdr_end = off = 8

        for i in range(count):
            end = data.index(0, off)
            path_dirs[i] = _dec(data[off:end])[0]
            off = end + 1
        path_end = off

        for i in range(count):
            end = data.index(0, off)
            orig_dirs[i] = _dec(data[off:end])[0]
            off = end + 1
        orig_end = off

        for i,(path,origpath) in enumerate(zip(path_dirs, orig_dirs)):
            entries[i] = _Ent(path, origpath, *_u32_4(data, off), wad)
            off += 16
        ent_end = off
        
        return data, path_end, orig_end, ent_end, entries



#######################################################################################

del namedtuple, io, Any, Dict, Iterator, List, Optional, Tuple, Union  # cleanup declaration-only imports
