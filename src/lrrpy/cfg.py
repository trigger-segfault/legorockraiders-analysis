#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""CFG file reader
"""

__version__ = '0.0.1'
__date__    = '2021-06-19'
__author__  = 'Robert Jordan'

__all__ = ['CFG', 'CFGProp']

#######################################################################################

from collections import namedtuple
import io, os, re
from typing import Any, Dict, Iterator, List, Optional, Tuple, Union

from .util.file import check_header
from .util.common import TEXT_CODEC, S4_UINT32, UINT32_4
from .util.common import _tupleno__len__, _tupleno__iter__, _tupleno__getitem__, _tupleno__contains__, _tuplenoindex, _tuplenocount


#######################################################################################


# def join(*keyPaths:str) -> str:
#     return '::'.join(keyPaths)

# def split(keyPath:str) -> List[str]:
#     return keyPath.split('::')


class CFGProp:
    __slots__ = ('key', 'value', 'depth', 'previous', 'next', '_field_10')
    key:Optional[str]
    value:Optional[str]
    depth:int
    previous:Optional['CFG']
    next:Optional['CFG']
    _field_10:Optional[Any]

    def __init__(self, key:Optional[str]=None, value:Optional[str]=None, depth:int=0, previous:Optional['CFG']=None, next:Optional['CFG']=None, *, _field_10:Optional[Any]=None):
        # self.tokens = tokens
        self.key = key
        self.value = value
        self.depth = depth
        self.previous = previous
        self.next = next
        self._field_10 = _field_10
        # if previous is not None:
        #     previous.next = self
        # if next is not None:
        #     next.previous = self
    
    def isKeyMatch(self, keyName:str) -> Tuple[bool, bool]:
        isWildcard = False
        if self.depth == 0:
            idx = self.key.find('*')
            if idx != -1:
                isWildcard = self.key[:idx].lower() == keyName[:idx].lower()
        
        return (isWildcard or self.key.lower() == keyName.lower(), isWildcard)

    def getProp(self, keyPath:str) -> Optional['CFGProp']:
        parts = self.split(keyPath)
        numParts = len(parts)

        result = None  # type: Optional['CFGProp']
        prop = self  # type: 'CFGProp'

        while prop is not None:
            isWildcard = False
            depth = numParts - 1

            if prop.depth == depth:
                isMatch, isWildcard = prop.isKeyMatch(parts[depth])
                
                if isMatch:
                    previous = prop.previous
                    while previous is not None:
                        if previous.depth == depth - 1:
                            isMatch, isWildcard = previous.isKeyMatch(parts[depth - 1])
                            if not isMatch:
                                break
                            depth -= 1
                        previous = prop.previous

                    if depth == 0:
                        result = prop
                        if not isWildcard:
                            break
            prop = prop.next
        return result

    # previous = prop.previous
    # if prop.depth != depth:
    #     prop = prop.next
    #     continue
    # prop = prop.next
        
    @staticmethod
    def join(*keyPaths:str) -> str:
        return '::'.join(keyPaths)

    @staticmethod
    def split(keyPath:str) -> List[str]:
        return keyPath.split('::')
        
    def __repr__(self) -> str:
        return f'<{self.__class__.__name__}: {self.key!r} = {self.value!r}>'
    __str__ = __repr__

class CFG(CFGProp):
    __slots__ = CFGProp.__slots__ + ('path', 'mode', 'fp', 'data', 'tokens', 'props')
    path:str
    mode:str
    fp:io.BufferedReader
    data:bytes
    tokens:Optional[Tuple[str,...]]
    props:List[CFGProp]
    
    _RE_TOKENIZE = re.compile(r"[\t\n\r ]+|;[^\n]*(?:\n|$)", 0)
    _RE_TOKENIZE_B = re.compile(_RE_TOKENIZE.pattern.encode(), 0)

    def __init__(self, path:str, mode:str='r'):
        super().__init__(key=None, value=None, depth=0, previous=None)
        self.path = path
        self.mode = mode
        self.fp = None
        with open(path, 'rb') as fp:
            data, tokens, props = self._parse(fp, self)
        self.data = data
        self.tokens = tokens
        self.props = props


    @property
    def name(self, *, _basename=os.path.basename) -> str:
        return _basename(self.path)
    @property
    def dirname(self, *, _dirname=os.path.dirname) -> str:
        return _dirname(self.path)
    @property
    def ext(self, *, _splitext=os.path.splitext) -> str:
        return _splitext(self.path)[0].lower()

    def __len__(self) -> int:
        return len(self.props)
    def __iter__(self) -> Iterator[CFGProp]:
        return iter(self.props)
    def __contains__(self, entry:Union[str,CFGProp]) -> bool:
        if isinstance(entry, str):
            return self.getProp(entry) is not None
            # return entry.lower() in self.lookup
        return entry in self.props
    def __getitem__(self, key:Union[str,int,slice]) -> CFGProp:
        if isinstance(key, str):
            return self.getProp(key)
            # return self.lookup[key.lower()]
        return self.props[key]

    # def get(self, key:str, default:Any=None) -> Optional[CFGProp]:
    #     return self.lookup.get(key, default)

    def __repr__(self) -> str:
        return f'{super().__repr__()[:-1]} props={len(self.props)}>'
        # return f'<{self.__class__.__name__}: props={len(self.props)}>'
    __str__ = __repr__
    
    @classmethod
    def _tokenize(cls, textdata:Union[str,bytes], *, _dec=TEXT_CODEC.decode) -> Tuple[str,...]:
        if isinstance(textdata, str):
            return tuple(s for s in cls._RE_TOKENIZE.split(textdata) if s)
        return tuple(_dec(s)[0] for s in cls._RE_TOKENIZE_B.split(textdata) if s)
    
    @classmethod
    def _parse(cls, reader:io.BufferedReader, root:Optional['CFG']=None, *, _Prop=CFGProp) -> Tuple[bytes, Tuple[str,...], List[CFGProp]]:
        textdata = reader.read()
        tokens = cls._tokenize(textdata)

        props = []
        if root is not None:
            root.tokens = tokens
        else:
            root = CFGProp()
        p = root

        for t in tokens:
            if t == "}":
                if p.key is not None and p.value is None:
                    print(f'Unexpected block closed before prop {p!r} value')
                p.depth -= 1
            
            elif p.key is None:
                if t == "{":
                    print(f'Unexpected key value "{{", last property = {p.previous!r}')
                p.key = t
            
            else:
                p.value = t

                props.append(p)
                p = CFGProp(previous=p, depth=p.depth)
                p.previous.next = p

                if t == "{":
                    p.depth += 1
        
        if p.key is not None:
            if p.key is None:
                print(f'final prop {p!r} missing value!')
            else:
                props.append(p)
        
        if p.depth != 0:
            print(f'final prop {p!r} not at depth 0, depth = {p.depth}')
        
        return textdata, tokens, props


    # @classmethod
    # def validate(cls, textdata:Union[str,bytes]):
    #     tokens = cls._tokenize(textdata)
        



#######################################################################################

del namedtuple, io, Any, Dict, Iterator, List, Optional, Tuple, Union  # cleanup declaration-only imports
