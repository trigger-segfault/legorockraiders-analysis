#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""LEGO Rock Raiders reversing tools library
"""

__version__ = '0.0.1'
__date__    = '2021-06-19'
__author__  = 'Robert Jordan'

__all__ = ['WAD', 'WADEntry', 'CFG', 'CFGProp']

#######################################################################################

from .wad import WAD, WADEntry
from .cfg import CFG, CFGProp

# try:
#     # functions to load existing files quickly in the interactive shell
#     from tests import wadtest, cfgtest
# except:
#     pass


#######################################################################################

#region ## FILE SIGNATURES ##


## ALIASES:
WADFile = WAD
WADFileEntry = WADEntry


LETTERS_SEEN = ' +-.0123456789=ABCDEFGHIJKLMNOPQRSTUVWXYZ\\_abcdefghijklmnopqrstuvwxyz'

# def letterset(*texts:Union[str,bytes]) -> Union[str,bytes]:
#     from itertools import chain
#     unique = set(chain.from_iterable(texts))
#     if isinstance(texts[0], (bytes,bytearray)):
#         return b''.join(sorted(unique))
#     else:
#         return ''.join(sorted(unique))

"""
from lrrpy import *
from lrrpy.tests import *
cfg = cfgtest()
cfg
print('\n'.join(str(p) for p in cfg.props[:20]))

from itertools import chain
from lrrpy.util.common import letterset
from lrrpy import *
wad = wadtest()
wad
wad.entries[0]
wad.ent_end
any(e.version!=1 for e in wad.entries)
any(e.size!=e.size2 for e in wad.entries)
print('\n'.join(str(e) for e in wad.entries[:20]))
any(not e.path.isprintable() for e in wad.entries)
any('/' in e.path for e in wad.entries)
letters = set()
all_letters = set(chain.from_iterable(e.path for e in wad.entries))
len(all_letters)
letters = ''.join(sorted(all_letters))
letters
sum(int(' ' in e.path) for e in wad.entries)
[e for e in wad.entries if ' ' in e.path]
print('\n'.join([str(e) for e in wad.entries if ' ' in e.path]))
t = 'Creatures\\Snake\\body'.lower()
[e for e in wad.entries if e.path.lower().startswith(t)]
len([e for e in wad.entries if e.path.lower().startswith(t)])
print('\n'.join([str(e) for e in wad.entries if e.path.lower().startswith(t)]))

"""