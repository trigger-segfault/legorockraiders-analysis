#!/usr/bin/env python3
#-*- coding: utf-8 -*-
"""Automated transformation of Ghidra exported .h/.c and .txt (ASCII) files into a
more compact and readable format for committing to the GitHub repository.
"""

__version__ = '0.0.1'
__date__    = '2021-09-17'
__author__  = 'Robert Jordan'

#######################################################################################

import enum, io, os, re
import traceback
import functools, operator  # used by `def prod(iterable)`
import struct               # used by `def signed(value:int, byteSize:int) -> int`

from collections import namedtuple
from enum import auto
from typing import Any, Callable, Dict, Iterable, Iterator, List, Match, Optional, Pattern, Tuple, Type, Union

# <https://pypi.org/project/regex/>
# import regex  # PyPy regex with \G pattern meta escape
try:
    import regex
    REGEX_HAS_G_ESCAPE = True
except:
    import re as regex  # only here to make the linter happy, do not actually use this!
    REGEX_HAS_G_ESCAPE = False

#######################################################################################

#region GHIDRA EXPORT INSTRUCTIONS

# Instructions for Exporting Ghidra programs.
# To format and then present to a **sane**
# compiler with added information.

#==========================================
# Code Browser: <ProgramPath>
#==========================================
# File > Export Program...

#==========================================#
# Export <ProgramName>                   X #
#==========================================#
#      Format: [<see below>          v ]   # REQUIRED FORMAT
# Output File: [LegoRR_<ISO>(-suf)][...]   # (OPTIONAL) e.g. "LegoRR_2021-09-30" or "LegoRR_2021-09-30-aa" (for suffix, etc.)
#                                          #
#                         [ Options... ]   # NEXT STEP
#------------------------------------------# (these options reset after every export... *sigh*)

###########################################################################

#region GHIDRA EXPORT FORMAT: Ascii

# Output extension: .txt    (do not include in Output File name)
# Ascii export is used to scrape:
#  - function addresses
#  - global variables and addresses

#==========================================#
# Options                                X # (The look of the Options window is specific to certain formats)
#==========================================#
# -Advanced------------------------------- # LABEL   = relied upon for globals
# Label Suffix  :     Comment Prefix  ;    # COMMENT = relied upon for functions
# ---------------------------------------- #
#     Comments [ ]        Properties [ ]   #
#   Structures [ ]    Undefined Data [ ]   #
#  Ref Headers [ ]         Back Refs [ ]   #
# Forward Refs [ ]         Functions [ ]   #
#  Block Names [ ]                         #
# ---------------------------------------- #
#         [Select All]  [Deselect All] <---#- PRESS DESELECT (unchecks all above)
#                                          #
# -Width---------------------------------- #
#          Labels: 80        Address: 10   # ESSENTIAL = Address
#           Bytes: 0     PreMnemonic: 0    #
#        Mnemonic: 50        Operand: 512  # ESSENTIAL = Mnemonic
#     End of Line: 100    References: 0    # (Many zeros are relied upon so that a field won't exist)
# Data Field Name: 0                       # (Other non-zeros need enough space to avoid clipping)
#------------------------------------------#

#endregion

###########################################################################

#region GHIDRA EXPORT FORMAT: C/C++

# Output extension: .h/.c  (do not include in Output File name)
# C/C++ export is used to scrape:
#  - datatype definitions
#  - function declarations (with calling convention)

#==========================================#
# Options                                X # (The look of the Options window is specific to certain formats)
#==========================================#
#      Create Header File (.h) [X]         # REQUIRED
#           Create C File (.c) [ ]         # (optional, does not effect parsing)
#  Use C++ Style Comments (//) [X]         # ESSENTIAL
#   Emit Data-type Definitions [X]         # ESSENTIAL = datatypes are needed for parsing everything else
#  Function Tags to Filter [HIDDEN,_STD_]  # QOL = hide all irrelevant functions/standard library functions
#       Function Tags Excluded [X]         # QOL (for above)
#------------------------------------------#

#endregion

#endregion

#######################################################################################

#region ## CONFIGURABLE DEFAULTS ##

#NOTE: assumes this script is in the directory "<repo>/src/*/"
SCRIPT_DIR:str = os.path.abspath(os.path.dirname(__file__))
EXPORT_DIR:str = os.path.abspath(os.path.join(SCRIPT_DIR, r"../../export"))
OUTPUT_DIR:str = os.path.abspath(os.path.join(SCRIPT_DIR, r"../../../data/source_dump"))

FILENAME_FMT:str = r"LegoRR_{0}{1}" # r"LegoRR_{ISODATE}{ext=.h,.c,.txt}"

# IGNORE_FILES:list = ["_backup"]
# IGNORE_EXTS:list  = []

H_EXT:str     = r".h"
C_EXT:str     = r".c"
ASCII_EXT:str = r".txt"

RE_FLAGS:re.RegexFlag = re.ASCII | re.MULTILINE #| re.DOTALL

PAD_DEFAULT:bool = True  # default for padding when using Symbol.print
ENUM_SORT_DEFAULT:bool = True  # default to sorting enums by numerical value

#endregion


#######################################################################################

#region NUMBER HELPERS

# <https://stackoverflow.com/a/7948307/7517185>
def prod(iterable:Iterable) -> Iterable:
    """math.prod support for Python versions < v3.8"""
    return functools.reduce(operator.mul, iterable, 1)


def signed(value:int, byteSize:int) -> int:
    """Unsigned to signed integer type"""
    if value < 0: return value  # already signed
    
    if byteSize == 1: return struct.unpack('=b', struct.pack('=B', value))[0] # & 0xff))[0]
    if byteSize == 2: return struct.unpack('=h', struct.pack('=H', value))[0] # & 0xffff))[0]
    if byteSize == 4: return struct.unpack('=i', struct.pack('=I', value))[0] # & 0xffffffff))[0]
    if byteSize == 8: return struct.unpack('=q', struct.pack('=Q', value))[0] # & 0xffffffffffffffff))[0]

#endregion


#######################################################################################

#region REGEX SUBSTITUTION FUNCTIONS

###########################################################################
## compact undefined struct fields into one
## from:
#    undefined field_0xc;
#    undefined field_0xd;
#    undefined field_0xe;
#    undefined field_0xf;
#    undefined field_0x10;
#    undefined field_0x11;
#    undefined field_0x12;
#    undefined field_0x13;
#
## into:
#    undefined field_0xc_0x13[0x8];

# match a minimum of 8 (6+2) or more field_0x's
FIELD0X_MIN = 2 # 8
FIELD0X_PAT = re.compile(r"^\tundefined field_0x([0-9a-f]+);(?:\n\tundefined field_0x[0-9a-f]+;){" + str( FIELD0X_MIN-2 ) + r",}\n\tundefined field_0x([0-9a-f]+);", RE_FLAGS)
# FIELD0X_FIELD = re.compile(r"^\tundefined field_0x([0-9a-f]+);\n(?:\tundefined field_0x[0-9a-f]+;\n){" + FIELD0X_MIN + r",}\tundefined field_0x([0-9a-f]+);", RE_FLAGS)
FIELD0X_REPL = lambda m: f"\tundefined field_0x{m.group(1)}_0x{m.group(2)}[{(int(m.group(2),16)+1-int(m.group(1),16)):#x}];" # length goes in {0}

def sub_compact_field0x(s:str) -> str:
    return FIELD0X_PAT.sub(FIELD0X_REPL, s)


###########################################################################
## replace CRLF "\r\n" newlines with simple LF "\n" newlines

CRLF_PAT = re.compile("[\r][\n]", RE_FLAGS)
CRLF_REPL = "\n"

def sub_crlf2lf(s:str) -> str:
    return CRLF_PAT.sub(CRLF_REPL, s)


###########################################################################
## replace CRLF "\r\n" newlines with simple LF "\n" newlines
##  AND trim all excess trailing whitespace and empty lines

TRIMLINES_PAT = re.compile(r"[ \t\n\r]+(?=\n)", RE_FLAGS)

def rem_trimlines(s:str) -> str:
    return TRIMLINES_PAT.sub("", s)


###########################################################################
## replace leading spaces with tabs of a designated size

# With the parsing speed, this really isn't a performance hit to use re + lambdas...
if REGEX_HAS_G_ESCAPE: # and False:
    SPACES2TABS_PAT = regex.compile(r"^(?:\G|^)[ ]{2}", RE_FLAGS)
    SPACES2TABS_REPL = '\t'

    SPACES4TABS_PAT = regex.compile(r"^(?:\G|^)[ ]{4}", RE_FLAGS)
    SPACES4TABS_REPL = '\t'

else:
    SPACES2TABS_PAT = re.compile(r"^([ ]{2})", RE_FLAGS)
    SPACES2TABS_REPL = lambda m: '\t' * (len(m[1]) // 2)

    SPACES4TABS_PAT = re.compile(r"^([ ]{4})", RE_FLAGS)
    SPACES4TABS_REPL = lambda m: '\t' * (len(m[1]) // 4)

# for C source
def sub_spaces2tabs(s:str) -> str:
    return SPACES2TABS_PAT.sub(SPACES2TABS_REPL, s)

# for H header
def sub_spaces4tabs(s:str) -> str:
    return SPACES4TABS_PAT.sub(SPACES4TABS_REPL, s)


###########################################################################
# remove C-style struct/enum/union type prefixes

CTYPEFIELD_PAT = re.compile(r"^\t(?:struct|enum|union)(?=[ \t])")
CTYPEFIELD_REPL = "\t"

def sub_ctypefield(s:str) -> str:
    return CTYPEFIELD_PAT.sub(CTYPEFIELD_REPL, s)


###########################################################################
# strip typedefs from enums: [^\n]+ ensures we escape first-line comments
#                            [^}]+? then reads until the end of the enum and backtracks
TYPEDEFENUM_PAT = re.compile(r"^typedef (enum[^\n]+\n)([^}]+?)(\n\})[^;]*(;)")
TYPEDEFENUM_REPL = r"\1\2,\3\4" # added final comma just keeps things uniform for later parsing, it's not essential

def sub_typedefenum(s:str) -> str:
    return TYPEDEFENUM_PAT.sub(TYPEDEFENUM_REPL, s)


###########################################################################
# remove autogenerated: typedef struct MyStruct MyStruct, *PMyStruct;
CTYPEDEF_PAT = re.compile(r"^typedef\s+(struct|union)\s(?P<name>[A-Za-z_][0-9A-Za-z_]*)\s(?P=name),\s\*P(?P=name);\n$", RE_FLAGS)

def rem_ctypedef(s:str) -> str:
    return CTYPEDEF_PAT.sub("", s)


###########################################################################
# remove ghidra defines: (exclude code)
DEFINE_PAT = re.compile(r"^#define (?!code )[^\n]+\n", RE_FLAGS)

def rem_define(s:str) -> str:
    return DEFINE_PAT.sub("", s)


###########################################################################
# remove useless "float10;" typedef abomination
# fix useless "float10;" typedef abomination
FLOAT10_PAT = re.compile(r"^(float10)$", RE_FLAGS)
FLOAT10_REPL = r"typedef long double \1;"
def sub_float10(s:str) -> str:
    return FLOAT10_PAT.sub(FLOAT10_REPL, s)


###########################################################################
# remove "xxxxxxxx   -> xxxxxxxx   [UNDEFINED BYTES REMOVED]" from ascii output
UNDEFINEDBYTES_PAT = re.compile(r"""^[a-f0-9]{8}[ ]{3}->[ ][a-f0-9]{8}[ ]{3}\[UNDEFINED[ ]BYTES[ ]REMOVED\]$""", RE_FLAGS)

def rem_undefinedbytes(s:str) -> str:
    return UNDEFINEDBYTES_PAT.sub("", s)


###########################################################################
# remove predefined C-strings from ascii output global variables
REMOVEGLOBALCSTRING_PAT = re.compile(r"""^[ ]{10}s_[^\n\s]*_[a-f0-9]{8}:\n[a-f0-9]{8}[ ]{2}ds[ ]{48}".*"$""", RE_FLAGS)

def rem_globalcstring(s:str) -> str:
    return REMOVEGLOBALCSTRING_PAT.sub("", s)


###########################################################################
# remove predefined floating point constants used in calculations
REMOVECONSTFLOATING_NOLAB_PAT = re.compile(r"""^(?<!:\n)[a-f0-9]{8}[ ]{2}(?:float[ ]|double)[ ]{44}(?!\?\?).+$""", RE_FLAGS)

REMOVECONSTFLOATING_LAB_PAT = re.compile(r"""^[ ]{10}(?:FLOAT_[a-f0-9]{8}[ ]|DOUBLE_[a-f0-9]{8}):\n[a-f0-9]{8}[ ]{2}(?:float[ ]|double)[ ]{44}(?!\?\?).+$""", RE_FLAGS)

def rem_constfloating(s:str) -> str:
    return REMOVECONSTFLOATING_LAB_PAT.sub("", REMOVECONSTFLOATING_NOLAB_PAT.sub("", s))


###########################################################################
# use to find a final ASM instruction to separate functions from globals in ascii output
FINDGLOBALSTART_PAT = re.compile(r"""^[a-f0-9]{8}[ ]{2}(?:JN?[ZGL]|JMP|CALL|I?RET|NOP)(?: [^\n]*)?$""", RE_FLAGS)
# used to find the first DLL import to separate globals from remaining C runtime/EXE data
FINDGLOBALEND_PAT = re.compile(r"""^[ ]{10}PTR_[A-Za-z_][A-Za-z_0-9]*_[a-f0-9]{8}:\n[a-f0-9]{8}[ ]{2}addr[ ]{46}[A-Za-z0-9_\-]+\.[A-Za-z]{3}::[A-Za-z_][A-Za-z_0-9]*$""", RE_FLAGS)

def find_globalspan(s:str) -> Tuple[int,int]:
    start = end = None
    m1 = None  # we need to find the last match
    for m in FINDGLOBALSTART_PAT.finditer(s):
        m1 = m
    if m1: start = m1.span(0)[1]  # end of this match is start of globals
    
    m2 = FINDGLOBALEND_PAT.search(s, start or 0)
    if m2: end   = m2.span(0)[0]  # start of this match is end of globals

    return (start, end)

def split_functionglobalspans(s:str) -> Tuple[str,str]: # (functions, globals)
    start,end = find_globalspan(s)
    if start is None or end is None:
        return (None,None)
    return (s[0:start], s[start:end])

#endregion


#######################################################################################

#region BIG LIST OF UNORGANIZED REGEX PATTERNS

###########################################################################

# GHIDRA_ALLOWED_TYPEDEFS = {'byte', 'uchar', 'ushort', 'uint', 'ulong', 'longlong', 'ulonglong', 'undefined', 'undefined1', 'undefined2', 'undefined4', 'undefined8', 'float10'}

ALLOWED_TYPEDEFS = {'Mesh_TextureStateChangeData', 'Mesh_Texture', 'Material', 'Animation_t', 'Movie_t', 'Material_t'}

EXCLUDE_FUNCTYPEDEFS = {'QsortCompare', 'PTOP_LEVEL_EXCEPTION_FILTER', '_PNH', 'WNDPROC', 'DLGPROC', 'MMIOPROC', 'FARPROC'}

# RE_SYM    = r"A-Za-z_0-9"
# # RE_NSYM    = r"[^A-Za-z_0-9]"

# RE_YSYM    = r"[A-Za-z_0-9\/\n]"

RE_SYM     = r"[A-Za-z_0-9]"
RE_NSYM    = r"[^A-Za-z_0-9\/\n]"


# RE_BLOCKCOMMENT_CAP = r"(?:\/\*\s*((?:[^*]|\*\/)*?)\s*\*\/)"
# RE_COMMENT_CAP = r"(?:\/(?:(\*)|(\/))\s*((?:[^*]|\*\/)*?)\s*\*\/"

WS1 = r"[^\S\r\n]"
# WS1N = r"\s"
# whitespace including block comments
WS = r"(?:[^\S\r\n\/]|(?:\/\*\s*(?:[^*]|\*[^\/])*\s*\*\/)|\/[^\/])"
# whitespace including block comments and newlines
WSN = r"(?:[^\S\/]|(?:\/\*\s*(?:[^*]|\*[^\/])*\s*\*\/)|\/[^\/])"
# whitespace including all comments
WS2 = r"(?:[^\S\r\n\/]|(?:\/\*\s*(?:[^*]|\*[^\/])*\s*\*\/)|(?:\/\/+[^\S\r\n]*(?:[^\n]|\\\n)*)"

RE_IDENTIFIER = r"(?:[A-Za-z_][A-Za-z_0-9]*)"

# edge cases for more stupid ghidra shenanigans
RE_SYMBOL_TYPE = rf"(?:char\[0\]|long{WS}+double|(?:signed|unsigned{WS}+)?(?:int|(?:char|short|long|long{WS}+long)(?:{WS}+int)?)|[A-Za-z_][A-Za-z_0-9]*)"
# RE_SYMBOL      = r"(?:[A-Za-z_][A-Za-z_0-9]*)"

RE_SINTEGER   = r"(?:(?:0[Xx][A-Fa-f0-9]+|[+\-]?[0-9]+)(?:[Uu][Ll]?[Ll]?|[Ll][Ll]?[Uu]?)?)"
RE_UINTEGER   = r"(?:(?:0[Xx][A-Fa-f0-9]+|\+?[0-9]+)(?:[Uu][Ll]?[Ll]?|[Ll][Ll]?[Uu]?)?)"

RE_MODIFIER  = rf"(?:const|volatile|IN|OUT|OPTIONAL|_(?:In|Out|Inout(?:_opt)?)_)" #|\[\[noreturn\]\]|extern{WS}+\"C\")"

RE_PTR = r"\*"

RE_ARRAY     = rf"(?:\[{RE_UINTEGER}\])"
RE_ARRAY_COUNT     = rf"(?:\[({RE_UINTEGER})\])"

RE_DECL = r"(?:__(?:cdecl|stdcall|thiscall|fastcall))"

RE_MODIFIERS = rf"(?:{RE_MODIFIER}(?:{WS}+{RE_MODIFIER})*)"
RE_PTRS = rf"(?:{RE_PTR}(?:{WS}*{RE_PTR})*)"
RE_ARRAYS = rf"(?:{RE_ARRAY}(?:{WS}*{RE_ARRAY})*)"
# global namespace "::" or optional global prefix "::<namespace>::<name>::" or just "<namespace>::<name>::"
RE_NAMESPACE = rf"(?: :: | (?: :: )? (?: {RE_IDENTIFIER}:: )+ )"

RE_CSTYLEKEYWORD = r"(?:struct|union|enum)"

##HACK: Handle up to 3 levels of nested function pointers
RE_ARGUMENTS_BASE = r"[^;()\/\n]*"
for _ in range(3):
    RE_ARGUMENTS_BASE = rf"\((?:[^;()\/\n]|{RE_ARGUMENTS_BASE})*\)"
RE_ARGUMENTS = rf"(?:{RE_ARGUMENTS_BASE})"


# RE_BLOCKCOMMENT_CAP = r"(?:\/\*\s*((?:[^*]|\*\/)*?)\s*\*\/)"
# RE_COMMENT_CAP = r"(?:\/(?:(\*)|(\/))\s*((?:[^*]|\*\/)*?)\s*\*\/"

# RE_LINECOMMENT = r"(?:\/\/[^\n]+)"

# RE_LINECOMMENT_CAP = r"(?:\/\/+\s*(?:(?P<comment>(?:[^\n]|\\\n)*?))\s*)?(?=\n|$)"

RE_LINECOMMENT_CAP = rf"(?:\/\/+{WS1}*(?:(?P<comment>(?:[^\n]|\\\n)*)))?" #{WS}*(?=\n))?"


RE_PARSE_SYMBOL = rf"""
    (?: (?P<modifier>{RE_MODIFIERS}) {WSN}* )?                   # symbol type modifiers

    (?: {RE_CSTYLEKEYWORD} {WSN}* )?   # C-style struct|union|enum before type name
    (?<!{RE_SYM}) (?P<typename>{RE_SYMBOL_TYPE}) (?!{RE_SYM}) {WSN}*  # REQUIRED: symbol type name
    (?: (?P<typeptrs>{RE_PTRS}) {WSN}* )?                        # outside pointers "typeptrs"

    (?: (\() {WSN}* )?      # enclosing () for function pointers and pointers to fixed arrays

        (?: (?P<decl>{RE_DECL}) {WSN}* )?     # function declaration type
        (?: (?P<nameptrs>{RE_PTRS}) {WSN}* )? # enclosed pointers "nameptrs"
        # (?: (?<!{RE_SYM}) (?P<name>{RE_IDENTIFIER}) (?!{RE_SYM}) {WSN}* )? # symbol name
        
        (?: (?<!{RE_SYM})
            (?: (?P<namespace> {RE_NAMESPACE} ) )?
            (?P<name>{RE_IDENTIFIER}) (?!{RE_SYM}) {WSN}*
        )? # symbol name

    (?(4) \) {WSN}* |)      # match closing ()

    (?: (?P<arguments>{RE_ARGUMENTS}) {WSN}* )?  # function arguments

    (?: (?P<arrays>{RE_ARRAYS}) {WSN}* )?        # arrays
"""

PARSE_TYPE_BLOCK = re.compile(rf"""
    ^
    (typedef {WS}+ )? (?P<keyword>struct|union|enum) {WS}+  # type keywords
    (?P<name>{RE_IDENTIFIER}) (?!{RE_SYM}) \s* #[{WS}\n]*  # type name
    \{{
        {WS}*{RE_LINECOMMENT_CAP}\n

        (?P<textbody> (?:[^}}\n]|\n[^}}])* )  # contents of block

    \n\}} {WS}*  # end of block brace
    (?(1) (?P<typedef>{RE_IDENTIFIER}) (?=[;,])) # optional typedef name
    [^\n;]*;   # semicolon terminator
""", RE_FLAGS | re.VERBOSE)

PARSE_ARRAYCOUNT = re.compile(rf"""
    \[
        (?P<count> {RE_UINTEGER} )
    \]
""", RE_FLAGS | re.VERBOSE)


PARSE_TYPEDEF = re.compile(rf"""
    ^
    typedef {WS}+

    {RE_PARSE_SYMBOL};

    (?(8)  | (?!))  # fail if we didn't match the typedef 'name' capture group
    #(?(8)|\0)  # fail if we didn't match the typedef 'name' capture group

""", RE_FLAGS | re.VERBOSE)

PARSE_FUNCTION_HEADER = re.compile(rf"""
    ^
    {RE_PARSE_SYMBOL};

    (?(6)  (?!) |)  # fail if we matched the 'nameptrs' capture group... this behavior isn't supported
    (?(8)  | (?!))  # fail if we didn't match the function 'name' capture group
    (?(9)  | (?!))  # fail if we didn't match the function 'arguments' capture group
    (?(10) (?!) |)  # fail if we matched the 'arrays' capture group... that's not part of a function

""", RE_FLAGS | re.VERBOSE)


PARSE_NAME = re.compile(rf"""
    # \t  # start of line

    # make '#' illegal too, due to preprocessors
    (?<![A-Za-z_0-9#]) (?P<typename>{RE_IDENTIFIER}) (?!{RE_SYM})

""", RE_FLAGS | re.VERBOSE)

PARSE_PREPROCESSOR = re.compile(rf"""
    #(?<![^\n]) {WS}*  # start of line

    # escape '#' ( '\#' or '[#]' ) because of extended (VERBOSE) flag
    #[#](?P<name> {RE_IDENTIFIER} )
    [#](?P<preprocessor> ( define ) | {RE_IDENTIFIER} )

    (?(2) (?: # define-only
        {WS1}+ (?P<name> {RE_IDENTIFIER} )

        # macro function arguments cannot have space after define name... right?
        (?: (?P<arguments> \( (?:[^\/\\\n()] | \/[^\/*()] | \\[^\n()])+ \) ) )?  # macro function arguments

    | # nothing extra to match for non-defines
    ) )

    # lazy quantifier so that we can strip trailing space
    #                                  |no comments| double-negative check forwards for '\n' or nothing
    (?: {WS1}+ (?P<output> (?:
        (?(2) (?: # define-only
                (?P<value> {RE_SINTEGER} )
                    |
                (?P<typename> {RE_SYMBOL_TYPE} )
        ) | (?!) )? # negative empty lookahead to fail this group, then we fall through to ?P<unknown>
            |
        (?P<unknown> (?:[^\/\\\n] | \/[^\/*] | \\[^\n])+? )
    ) ) )?

    # optional comment above define
    {WS1}* {RE_LINECOMMENT_CAP} #(?=\n|$)

""", RE_FLAGS | re.VERBOSE)

PARSE_MEMBER = re.compile(rf"""
    # \t  # start of line
    #(?: {RE_CSTYLEKEYWORD} {WS}+ )?
        {RE_PARSE_SYMBOL}   # generic symbol parsing
    ;            # end of member
    {WS}* {RE_LINECOMMENT_CAP}
""", RE_FLAGS | re.VERBOSE)


PARSE_PARAM = re.compile(rf"""
    (?:
    #(?: {RE_CSTYLEKEYWORD} {WS}+ )?
        {RE_PARSE_SYMBOL}       # generic symbol parsing
    )
        |
    ## WARNING: This must be the SECOND choice after RE_PARSE_SYMBOL, as that pattern depends on its numbered capture groups
    (?P<ellipsis> \.\.\. )
        # boundary of argument
""", RE_FLAGS | re.VERBOSE)

PARSE_ENUMVALUE = re.compile(rf"""
     #\t  # start of line
        (?P<name>{RE_IDENTIFIER}) {WS}*  # value name
            = {WS}*
        (?P<value>{RE_SINTEGER})   {WS}*  # integer value
    (?P<comma> , {WS}* )? #(?P<comment>)  # comma separator
     {RE_LINECOMMENT_CAP}
""", RE_FLAGS | re.VERBOSE)


### ASCII FILE REGEX ###

PARSE_FUNCTION_ASCII_ORIG = re.compile(r"""^[a-f0-9]{8}[^\n]*\n[ ]{10};(?P<function>[^\n]+)(?:\n[ ]{10}[; ][^\n]*)*(?:\n(?P<address>[a-f0-9]{8})[ ]{2})""", RE_FLAGS)

PARSE_FUNCTION_ASCII = re.compile(r"""^[ ]{10};(?P<function>[^\n]+)(?:\n[ ]{10}[; ][^\n]*)*(?:\n(?P<address>[a-f0-9]{8})[ ]{2})""", RE_FLAGS)


# RE_CONST_STRING = re.compile(r"""^(?:[ ]{10}(?P<name>s_[^\n\s]+_[a-f0-9]{8}):\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>ds)[ ]{48}(?P<value_raw>".*")$""", RE_FLAGS)


# RE_CONST_FLOAT_NOLAB = re.compile(r"""^(?<!:\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>float)[ ]{45}(?!\?\?)(?P<value>.+)$""", RE_FLAGS)

# RE_CONST_FLOAT = re.compile(r"""^(?:[ ]{10}(?P<name>FLOAT_[a-f0-9]{8}):\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>float)[ ]{45}(?!\?\?)(?P<value>.+)$""", RE_FLAGS)
# # RE_CONST_FLOAT = re.compile(r"""^(?:[ ]{10}(?P<name>FLOAT_[a-f0-9]{8}):\n)?(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>float)[ ]{45}(?!\?\?)(?P<value>.+)$""", RE_FLAGS)


# RE_CONST_DOUBLE_NOLAB = re.compile(r"""(?<!:\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>double)[ ]{44}(?!\?\?)(?P<value>.+)$""", RE_FLAGS)

# RE_CONST_DOUBLE = re.compile(r"""^(?:[ ]{10}(?P<name>DOUBLE_[a-f0-9]{8}):\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>double)[ ]{44}(?!\?\?)(?P<value>.+)$""", RE_FLAGS)
# # RE_CONST_DOUBLE = re.compile(r"""^(?:[ ]{10}(?P<name>DOUBLE_[a-f0-9]{8}):\n)?(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>double)[ ]{44}(?!\?\?)(?P<value>.+)$""", RE_FLAGS)

# RE_IDL = re.compile(r"""^(?:[ ]{10}(?P<name>[A-Za-z_][A-Za-z_0-9]+):\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>GUID)[ ]{46}(?P<value_raw>(?:(?P<value_name>.+?)[ ]+)?(?P<value>[a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12}))$""", RE_FLAGS)

RE_GLOBALVAR = r"""^(?:[ ]{10}(?P<name>[^\n\s]+):\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>[A-Za-z_][A-Za-z_0-9]*)(?:[ \t]?(?P<typeptrs>(?:\*[ \t]?)+))?(?P<arrays>(?:\[\d+\])+)?"""

PARSE_GLOBALVAR_QQ = re.compile(rf"""{RE_GLOBALVAR}[ ]+(?P<value_raw>\?\?|NaP)$""", RE_FLAGS)

# must be used after stripping RE_GLOBAL_QQ
PARSE_GLOBALVAR_VALUE = re.compile(rf"""{RE_GLOBALVAR}[ ]+(?P<value_raw>.*)$""", RE_FLAGS)

PARSE_GLOBALVAR_EMPTY = re.compile(rf"""{RE_GLOBALVAR}$""", RE_FLAGS)

PARSE_GLOBALVAR_ALL = re.compile(rf"""{RE_GLOBALVAR}(?:[ ]+(?P<value_raw>.*))?$""", RE_FLAGS)


# RE_UNDEFINEDBYTES = re.compile(r"""^(?P<address>[a-f0-9]{8})   -> (?P<address2>[a-f0-9]{8})   \[UNDEFINED BYTES REMOVED\]$""", RE_FLAGS)

# # use to find a final ASM instruction to separate functions from globals in ascii output
# RE_ASCII_GLOBALSSTART = re.compile(r"""^[a-f0-9]{8}[ ]{2}(?:JN?[ZGL]|JMP|CALL|I?RET|NOP)(?: [^\n]*)?$""")
# # used to find the first DLL import to separate globals from remaining C runtime/EXE data
# RE_ASCII_GLOBALSEND = re.compile(r"""^[ ]{10}PTR_[A-Za-z_][A-Za-z_0-9]*_[a-f0-9]{8}:\n[a-f0-9]{8}[ ]{2}addr[ ]{46}[A-Za-z0-9_\-]+\.[A-Za-z]{3}::[A-Za-z_][A-Za-z_0-9]*$""", RE_FLAGS)

PARSE_GLOBALGUID = re.compile(r"""^(?:[ ]{10}(?P<name>[A-Za-z_][A-Za-z_0-9]+):\n)(?:(?P<address>[a-f0-9]{8})[ ]{2})(?P<typename>GUID)[ ]{46}(?P<value_raw>(?:(?P<value_name>.+?)[ ]+)?(?P<value>[a-f0-9]{8}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{4}-[a-f0-9]{12}))$""", RE_FLAGS)


# PARSE_STRUCTFIELD_PAT = re.compile(r"^\t ((?:\[ ;")

# typedef Main_StateChangeData Mesh_TextureStateChangeData;
# typedef void Animation_t;
# typedef void Movie_t;
# typedef G98CAnimation Animation_t;
# typedef G98CMovie Movie_t;
# typedef Container_Texture Mesh_Texture;
# typedef void Material;
# typedef IDirect3DRMMaterial2 Material;



# typedef int (__cdecl* QsortCompare)(void *, void *);

# typedef uint size_t;

# typedef LONG (* PTOP_LEVEL_EXCEPTION_FILTER)(struct _EXCEPTION_POINTERS *);
# typedef int (* _PNH)(size_t);
# typedef LRESULT (* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
# typedef INT_PTR (* DLGPROC)(HWND, UINT, WPARAM, LPARAM);
# typedef LRESULT (MMIOPROC)(LPSTR, UINT, LPARAM, LPARAM);
# typedef int (* FARPROC)(void);

#endregion


#######################################################################################

#region Symbol types

class SymbolKind(enum.IntEnum):
    PRIMITIVE = auto()
    STRUCT    = auto()
    CLASS     = auto()
    UNION     = auto()
    ENUM      = auto()
    FLAGS     = auto() # enum with [flags:] comment
    TYPEDEF   = auto() # typedef "anything but functions"
    FUNCTION  = auto()
    VARIABLE  = auto()

    VALUE     = auto() # special case, should not be added to symbol db
    MEMBER    = auto() # special case, should not be added to symbol db
    PARAM     = auto() # special case, should not be added to symbol db


class Symbol:
    PTR_SIZE:int = 4
    # @classmethod
    # def _arraycount(cls, arrays:Optional[List[int]]=None) -> int:
    #     if not arrays: return 1
    #     return prod(arrays)
    # @classmethod
    # def _arraysize(cls, size:int, arrays:Optional[List[int]]=None) -> int:
    #     if not arrays: return size
    #     return size * cls._arraycount(arrays)
    # @classmethod
    # def _pointersize(cls, size:int, pointers:Optional[int]=None) -> int:
    #     if not pointers: return size
    #     return cls.PTR_SIZE
    # @classmethod
    # def _calcsize(cls, size:int, pointers:Optional[int]=None, arrays:Optional[List[int]]=None) -> int:
    #     size = cls._pointersize(size, pointers)
    #     return cls._arraycount(size, arrays)

    # DB:'SymbolDatabase' = None

    parent:Optional['Symbol']
    kind:SymbolKind
    name:str
    _display_name:Optional[str]
    namespace:Optional[str]
    _size:Optional[int]
    comment:str
    textbody:str
    _hide:bool
    _evaled:bool
    tagged:Optional['TaggedComment']
    address:Optional[int]

    def __init__(self, kind:SymbolKind, name:str, *, display_name:Optional[str]=None, namespace:Optional[str]=None, size:Optional[int]=None, comment:Optional[str]=None, textbody:Optional[str]=None, address:Optional[int]=None, hide:bool=False, evaled:bool=False, parent:Optional['Symbol']=None, tagged:Optional['TaggedComment']=None):
        self.parent = parent
        #self.kind = SymbolKind(kind)  #HACK: Ensure we can use `is` operator
        self.kind = kind
        self.name = name
        self._display_name = display_name
        self.namespace = namespace
        self._size = size
        self.comment = comment
        self.textbody = textbody
        self._hide = bool(hide)
        self._evaled = bool(evaled)
        self.tagged = tagged
        self.address = address
    
    def forward(self) -> str:
        raise NotImplementedError(f'{self.__class__.__name__}.forward()')
    def declare(self) -> str:
        raise NotImplementedError(f'{self.__class__.__name__}.declare()')
    def define(self) -> str:
        raise NotImplementedError(f'{self.__class__.__name__}.define()')

    @classmethod
    def format_type(cls, typename:str, *, name:Optional[str]=None, modifier:Optional[str]=None, typeptrs:Optional[int]=None, decl:Optional[str]=None, nameptrs:Optional[int]=None, arguments:Optional[List[str]]=None, arrays:Optional[List[int]]=None, namespace:Optional[str]=None) -> str:
        if modifier is None: modifier = ''
        if typename is None: typename = ''
        if decl is None: decl = ''
        if name is None: name = ''
        
        # namespace name is full name with trailing '::', that way we can allow optional '::' global ns access
        if namespace is None: namespace = ''

        # str.join is used here so we can configure pointer spacing
        typeptrs = ''.join('*' * typeptrs) if typeptrs else ''
        nameptrs = ''.join('*' * nameptrs) if nameptrs else ''
        arrays   = ''.join(f'[{n}]' for n in arrays) if arrays else ''

        if arguments is None:
            arguments = ''
        else:
            arguments = '(' + (', '.join(a for a in arguments) if arguments else 'void') + ')'


        typepart = ' '.join(filter(bool, (modifier, f'{typename}{typeptrs}')))
        namepart = ' '.join(filter(bool, (f'{decl}{nameptrs}', f'{namespace}{name}')))
    
        if nameptrs:  # we need parenthesis around the pointers (+ name)
            return ' '.join(filter(bool, (typepart, f'({namepart}){arguments}{arrays}')))
        else:
            return ' '.join(filter(bool, (typepart, f'{namepart}{arguments}{arrays}')))

    

    def print(self, *, pad:bool=PAD_DEFAULT, **kwargs):
        print(str(self), **kwargs)
    
    def format(self, *, end:Optional[str]=None, **kwargs) -> str:
        # Ultra-lazy wrapper around Symbol.print()
        strio = io.StringIO()
        if end is None: end = ''
        self.print(file=strio, end=end, **kwargs)
        return strio.getvalue()
    
    def format_full(self, *, end:Optional[str]=None, namespace:bool=True, address:bool=True, exename:str='LegoRR.exe', **kwargs) -> str:
        text = self.format(end=end, **kwargs)
        if not namespace and self.namespace:
            text = text.replace(self.namespace, '')
        if address and self.address is not None:
            text = f'// <{exename} @{self.address:08x}>\n{text}'
        return text
        
    def print_full(self, *, pad:bool=PAD_DEFAULT, end:Optional[str]=None, **kwargs):
        # An EVEN LAZIER wrapper around a wrapper around Symbol.print()
        #  This is so bad...
        print(self.format_full(pad=pad, **kwargs), end=end)

    @property
    def is_function(self) -> bool: return False
    
    @property
    def is_ellipsis(self) -> bool: return False

    @property
    def is_pointer(self) -> bool: return False

    @property
    def is_array(self) -> bool: return False
    
    @property
    def is_value(self) -> bool: return False
    
    @property
    def is_flags(self) -> bool: return False

    @property
    def basesize(self) -> Optional[int]: return self.size

    @property
    def size(self) -> Optional[int]: return self._size
    
    @property
    def has_size(self) -> bool: return self.size is not None

    @property
    def repeat(self) -> int: return 1
    
    @property
    def targetsize(self) -> Optional[int]: return None
    
    @property
    def display_name(self) -> Optional[str]: return self._display_name if self._display_name is not None else self.name
    @display_name.setter
    def display_name(self, new_display_name:Optional[str]): self._display_name = new_display_name
    
    @property
    def hide(self) -> bool: return self._hide
    @hide.setter
    def hide(self, new_hide:bool): self._hide = bool(new_hide)
    
    @property
    def primitive(self) -> Optional['PrimitiveSymbol']: return None
    
    @property
    def needs_eval(self) -> bool: return not self._evaled
    @needs_eval.setter
    def needs_eval(self, new_needs_eval:bool): self._evaled = bool(new_needs_eval)
    
    def evaluate(self, db:'SymbolDatabase') -> bool:
        if not self._evaled:
            self._evaled = self._evaluate(db)
        return self._evaled

    def _evaluate(self, db:'SymbolDatabase') -> bool:
        """implement required evaluation for derived classes with this function"""
        return True


class PrimitiveSymbol(Symbol):
    def __init__(self, name:str, size:int, *, evaled:bool=True, hide:bool=True, **kwargs):
        if size is None:
            raise TypeError(f'{self.__class__.__name__} size cannot be None')
        super().__init__(SymbolKind.PRIMITIVE, name, size=size, evaled=evaled, hide=hide, **kwargs)
        
    def forward(self) -> str:
        raise ValueError(f'{self.__class__.__name__}.forward() primitive cannot be forward-declared')
    def declare(self) -> str:
        raise ValueError(f'{self.__class__.__name__}.declare() primitive cannot be declared')
    def define(self) -> str:
        raise ValueError(f'{self.__class__.__name__}.define() primitive cannot be define')
    
    def __repr__(self):
        return f'primitive {self.display_name}'
    def __str__(self):
        return f'{self.display_name}'
    
    @property
    def primitive(self) -> Optional['PrimitiveSymbol']: return self


class TypeSymbol(Symbol):
    typename:str
    typeptrs:int
    nameptrs:int
    arrays:List[int]
    modifier:Optional[str]
    decl:Optional[str]
    type_symbol:Optional[Symbol]
    arguments:Optional[List['ParamSymbol']]
    _basesize:Optional[int]
    _is_function:bool
    
    def __init__(self, kind:SymbolKind, name:str, typename:str, *, typeptrs:int=0, nameptrs:int=0, arrays:List[int]=(), modifier:Optional[str]=None, decl:Optional[str]=None, is_function:bool=False, **kwargs):
        super().__init__(kind, name, size=None, **kwargs)
        self.typename = typename
        self.typeptrs = typeptrs
        self.nameptrs = nameptrs
        self.arrays = arrays
        self.modifier = modifier
        self.decl = decl
        self.type_symbol = None
        self.arguments = [] if bool(is_function) else None
        self._basesize = None
        self._is_function = bool(is_function)
    
    def __repr__(self):
        if not self.is_function:
            args = None
        elif self.arguments:
            args = [str(a) for a in self.arguments]
        else:
            args = ['void']
        
        name = self.display_name # self.name
        typename = self.display_typename # self.typename
        return f'{Symbol.format_type(typename, name=name, modifier=self.modifier, decl=self.decl, typeptrs=self.typeptrs, nameptrs=self.nameptrs, arrays=self.arrays, arguments=args, namespace=self.namespace)}'
    __str__ = __repr__

    ##HACK: Added to deal with overriding symbol names in the database
    @property
    def display_typename(self) -> str: return self.typename if self.type_symbol is None else self.type_symbol.display_name


    def add_argument(self, arg:'ParamSymbol') -> None:
        if not self._is_function:
            raise ValueError(f'{self.__class__.__name__}.add_argument() : cannot add argument to symbol of kind {self.kind.name}')
        arg.index = len(self.arguments)
        self.arguments.append(arg)
    
    @property
    def is_ellipsis(self) -> bool: return self.typename is not None and self.typename == '...'

    @property
    def is_function(self) -> bool: return self._is_function

    @property
    def is_pointer(self) -> bool: return bool(self.nameptrs or self.typeptrs)

    @property
    def is_array(self) -> bool: return bool(self.arrays)

    @property
    def basesize(self) -> Optional[int]: return self._basesize

    @property
    def repeat(self) -> int: return prod(self.arrays) if (not self.nameptrs and self.arrays) else 1

    @property
    def primitive(self) -> Optional['PrimitiveSymbol']:
        # if self.kind is not SymbolKind.TYPEDEF:
        #     return None
        #if isinstance(self, PrimitiveSymbol):
        type_sym = self #.type_symbol
        while type_sym is not None and type_sym.kind is SymbolKind.TYPEDEF:
            type_sym = self.type_symbol
        if type_sym is not None and type_sym.kind is SymbolKind.PRIMITIVE:
            return self
        return None
        #     if isinstance(type_sym, PrimitiveSymbol):
        #         return type_sym
        #     if isinstance(type_sym, Type):
        #         return type_sym
        # if self.type_symbol is not None:
        #     if hasattr(self.type)
    
    def _evaluate(self, db:'SymbolDatabase') -> bool:
        if self.type_symbol is None:
            self.type_symbol = db.get(self.typename, allow_ellipsis=self.is_ellipsis) #True)


        if self.is_function:
            for arg in self.arguments:
                arg.evaluate(db)

            # ##FIXME: Add this back? "MMIOPROC" triggers this
            # if not self.nameptrs:
            #     # non-pointer function types cannot evaluate size
            #     print(f'BAD {self!r}')
            #     return self.type_symbol is not None

        if not self.has_size:
            if self.is_ellipsis:
                self._size = self._basesize = 0

            elif self.nameptrs or self.is_function:
                self._size = self._basesize = Symbol.PTR_SIZE
                ##DEBUG: testing
                #return True
            
            elif self.typeptrs:
                self._basesize = Symbol.PTR_SIZE
                self._size = self._basesize * self.repeat
                ##DEBUG: testing
                #return True
            
            elif self.type_symbol is not None:
                ##TODO: Make as many passes as needed until all symbols are evalulated
                # if not self.type_symbol.has_size:
                #     self.type_symbol.evaluate(db)

                if self.type_symbol.has_size:
                    self._basesize = self.type_symbol.size
                    self._size = self._basesize * self.repeat
                    return True

            ##DEBUG: testing
            #return False  # we still need our underlying type size, can't evaluate

        return self.type_symbol is not None and self.has_size
        # return self.has_size  #self.type_symbol is not None and self.has_size


class TypedefSymbol(TypeSymbol):

    def __init__(self, name:str, typename:str, **kwargs):
        super().__init__(SymbolKind.TYPEDEF, name, typename, **kwargs)

    def __repr__(self):
        comment = f' // {self.comment}' if self.comment else ''
        return f'typedef {super().__repr__()};{comment}'
    def __str__(self):
        comment = f' // {self.comment}' if self.comment else ''
        return f'typedef {super().__str__()};{comment}'


class DefineTypedefSymbol(TypedefSymbol):

    def __init__(self, name:str, typename:str, **kwargs):
        super().__init__(name, typename, **kwargs)

    def __repr__(self):
        comment = f' // {self.comment}' if self.comment else ''
        return f'#define {self.display_name} {self.typename}{comment}'
    def __str__(self):
        comment = f' // {self.comment}' if self.comment else ''
        return f'#define {self.display_name} {self.typename}{comment}'


class FunctionSymbol(TypeSymbol):
    returnname:str
    returnsymbol:Optional[Symbol]

    def __init__(self, name:str, typename:str, **kwargs):
        super().__init__(SymbolKind.FUNCTION, name, typename, **kwargs)

    
    def __repr__(self):
        return f'{super().__repr__()};' # append semicolon ';'
    def __str__(self):
        return f'{super().__str__()};' # append semicolon ';'

class VariableSymbol(TypeSymbol):
    value:Optional[Any]
    value_raw:Optional[str]

    def __init__(self, name:str, typename:str, value:Optional[Any]=None, value_raw:Optional[str]=None, **kwargs):
        super().__init__(SymbolKind.VARIABLE, name, typename, **kwargs)
        self.value = value
        self.value_raw = value_raw
    
    def __repr__(self):
        ##TODO: = value append
        # if self.value is not None:
        #     if self.value is Ellipsis: # dummy shorthand for NULL
        #         value = f' = nullptr'
        #     elif isinstance(self.value, str):
        #         if self.value_raw is not None:
        #             value = f' = {self.value_raw}'
        #         else:
        #             value = repr(self.value)
        #             singlequote = (value[0] == '\'' and value[-1] == '\'')
        #             value = value[1:-1]
        #             if singlequote:
        #                 value = value.replace('\\\'', '\'').replace('\"', '\\\"')
        #             value = f' = {value}'
        #     elif isinstance(self.)
        # value = f' = self.value
        return f'{super().__repr__()};' # append semicolon ';'
    def __str__(self):
        return f'{super().__str__()};' # append semicolon ';'
        
    @property
    def is_value(self) -> bool: return self.value is not None or self.value_raw is not None



class ValueSymbol(Symbol):
    index:Optional[int]
    value:int

    def __init__(self, name:str, value:int, *, index:Optional[int]=None, **kwargs):
        super().__init__(SymbolKind.VALUE, name, size=None, evaled=True, **kwargs)
        self.value = value
        self.index = index
    
    @property
    def size(self) -> Optional[int]: return self.parent.size if self.parent is not None else None

    @property
    def is_flags(self) -> bool: return self.parent.is_flags if self.parent is not None else False
    @property
    def is_value(self) -> bool: return True

    # def __repr__(self):
    #     # comment = f' // {self.comment}' if self.comment else ''
    #     # # It's cleaner to format 0 flag values without the hex specified,
    #     # #  since most of the time these values are NONE and not a mask option
    #     # if self.value == 0:  # '0' for both flags and enums
    #     #     value = f'{self.value:d}'
    #     # elif self.is_flags:   # 0x-hex for flags
    #     #     value = f'{self.value:#x}'
    #     # else:                # decimal for normal enums
    #     #     value = f'{signed(self.value, self.targetsize or 4):d}'
    #     # return f'\t{self.display_name} = {value},{comment}'
    #     return f'\t{self!r}'
    def __repr__(self):
        return self.padstring(None)
        # comment = f' // {self.comment}' if self.comment else ''
        # # It's cleaner to format 0 flag values without the hex specified,
        # #  since most of the time these values are NONE and not a mask option
        # if self.value == 0:  # '0' for both flags and enums
        #     value = f'{self.value:d}'
        # elif self.is_flags:   # 0x-hex for flags
        #     value = f'{self.value:#x}'
        # else:                # decimal for normal enums
        #     value = f'{signed(self.value, self.targetsize or 4):d}'
        # return f'{self.display_name} = {value},{comment}'
    __str__ = __repr__
    
    def padstring(self, padlength:Optional[int]=None, **kwargs):
        comment = f' // {self.comment}' if self.comment else ''
        # It's cleaner to format 0 flag values without the hex specified,
        #  since most of the time these values are NONE and not a mask option
        if self.value == 0:  # '0' for both flags and enums
            value = f'{self.value:d}'
        elif self.is_flags:   # 0x-hex for flags
            value = f'{self.value:#x}'
        else:                # decimal for normal enums
            value = f'{signed(self.value, self.targetsize or 4):d}'
        return f'{self.display_name.ljust(padlength or 0)} = {value},{comment}'
        # text = f'{self!s}\n{{\n' + '\n'.join(f'\t{v!s}' for v in self.values) + f'\n}};'
        # text = 'enum' + text[4:]
        # if self.kind is SymbolKind.FLAGS:
        #     text += f'\nDEFINE_ENUM_FLAG_OPERATORS({self.display_name});'
        # print(text, **kwargs)

class DefineValueSymbol(ValueSymbol):

    def __init__(self, name:str, value:int, **kwargs):
        super().__init__(name, value, index=None, **kwargs)

    def __repr__(self):
        return self.padstring(None)
    __str__ = __repr__
    
    def padstring(self, padlength:Optional[int]=None, **kwargs):
        comment = f' // {self.comment}' if self.comment else ''
        # It's cleaner to format 0 flag values without the hex specified,
        #  since most of the time these values are NONE and not a mask option
        if self.value == 0:  # '0' for both flags and enums
            value = f'{self.value:d}'
        elif self.is_flags:   # 0x-hex for flags
            value = f'{self.value:#x}'
        else:                # decimal for normal enums
            value = f'{signed(self.value, self.targetsize or 4):d}'
        return f'#define {self.display_name.ljust(padlength or 0)} {value}{comment}'


class BaseEnumSymbol(Symbol):
    typename:Optional[str]
    type_symbol:Optional[Symbol]
    values:List[ValueSymbol]
    _targetsize:Optional[int]
    _is_flags:bool

    def __init__(self, kind:SymbolKind, name:str, typename:Optional[str]=None, *, is_flags:bool=False, targetsize:Optional[int]=None, **kwargs):
        super().__init__(kind, name, size=None, **kwargs)
        self.typename = typename
        self._targetsize = targetsize
        self.type_symbol = None
        self.values = []
        self._is_flags = is_flags

    def __repr__(self):
        keyname = 'flags' if self.is_flags else 'enum'
        typename = f' : {self.display_typename}' if self.typename else ''
        #typename = f' : {self.typename}' if self.typename else ''
        comment = f' // {self.comment}' if self.comment else ''
        return f'{keyname} {self.display_name}{typename};{comment}'
    def __str__(self):
        typename = f' : {self.display_typename}' if self.typename else ''
        #typename = f' : {self.typename}' if self.typename else ''
        comment = f' // {self.comment}' if self.comment else ''
        return f'enum {self.display_name}{typename}{comment}'
        
    ##HACK: Added to deal with overriding symbol names in the database
    @property
    def display_typename(self) -> str: return self.typename if self.type_symbol is None else self.type_symbol.display_name

    
    def add_value(self, value:ValueSymbol) -> None:
        value.parent = self
        value.index = len(self.values)
        self.values.append(value)
    
    def sort_values(self, *, key:Optional[Callable[[ValueSymbol],Any]]=None, reverse:bool=False) -> None:
        if key is None: key = lambda v: v.value
        self.values.sort(key=key, reverse=reverse)

        # update indices
        for i,v in enumerate(self.values):
            v.index = i
        
    def _evaluate(self, db:'SymbolDatabase') -> bool:
        if self.typename is None:
            if self._size is None:
                self._size = 4
            return True

        if self.type_symbol is None:
            self.type_symbol = db.get(self.typename)
        
        if self.type_symbol is not None:
            ##TODO: Make as many passes as needed until all symbols are evalulated
            # if not self.type_symbol.has_size:
            #     self.type_symbol.evaluate(db)

            if self.type_symbol.has_size:
                self._size = self.type_symbol.size
                return True

        return self.has_size  #self.type_symbol is not None and self.has_size
    
    @property
    def is_flags(self) -> Optional[int]: return self._is_flags

    @property
    def targetsize(self) -> Optional[int]: return self._targetsize
    
    def print(self, *, pad:bool=PAD_DEFAULT, **kwargs):
        padlength = None if not pad else max(len(v.display_name) for v in self.values)
        text = f'{self!s}\n{{\n' + '\n'.join(f'\t{v.padstring(padlength)}' for v in self.values) + f'\n}};'
        #text = f'{self!s}\n{{\n' + '\n'.join(f'\t{v!s}' for v in self.values) + f'\n}};'
        text = 'enum' + text[4:]
        if self.kind is SymbolKind.FLAGS:
            text += f'\nDEFINE_ENUM_FLAG_OPERATORS({self.display_name});'
        print(text, **kwargs)


class EnumSymbol(BaseEnumSymbol):
    def __init__(self, name:str, typename:Optional[str]=None, **kwargs):
        super().__init__(SymbolKind.ENUM, name, typename, is_flags=False, **kwargs)


class FlagsSymbol(BaseEnumSymbol):
    def __init__(self, name:str, typename:Optional[str]=None, **kwargs):
        super().__init__(SymbolKind.FLAGS, name, typename, is_flags=True, **kwargs)


class MemberSymbol(TypeSymbol):
    index:Optional[int]
    offset:Optional[int]

    def __init__(self, name:str, typename:str, *, index:Optional[int]=None, offset:Optional[int]=None, **kwargs):
        super().__init__(SymbolKind.MEMBER, name, typename, **kwargs)
        self.index = index
        self.offset = offset
    
    def __repr__(self):
        if self.parent is not None:
            off  = f'{self.offset:x}' if self.offset is not None else ''
            if off and self.parent.has_size:
                off = off.rjust(len(f'{self.parent.size:x}'), '0')
            
            size = f'{self.size:x}' if self.size is not None else ''

            pre = f'/*{off},{size}*/\t'
        else:
            pre = ''
        
        comment = f' // {self.comment}' if self.comment else ''
        return f'{pre}{super().__repr__()};{comment}'
    __str__ = __repr__


class ParamSymbol(TypeSymbol):
    index:Optional[int]
    offset:Optional[int]

    def __init__(self, name:str, typename:str, *, index:Optional[int]=None, offset:Optional[int]=None, **kwargs):
        super().__init__(SymbolKind.MEMBER, name, typename, **kwargs)
        self.index = index
        self.offset = offset
    
    # def __repr__(self):
    #     return f'{super().__repr__()}'
    # def __str__(self):
    #     return f'{super().__str__()}'


class BaseStructSymbol(Symbol):
    members:List[MemberSymbol]
    pack:Optional[int]
    _targetsize:Optional[int]

    def __init__(self, kind:SymbolKind, name:str, *, pack:Optional[int]=None, targetsize:Optional[int]=None, **kwargs):
        super().__init__(kind, name, **kwargs)
        self.pack = pack
        self._targetsize = targetsize
        self.members = []
    
    def add_member(self, member:MemberSymbol) -> None:
        member.parent = self
        member.index = len(self.members)
        # if self.kind is SymbolKind.STRUCT:
        #     if self.members:
        #         member.offset = self.members[-1].offset
        if self.kind is SymbolKind.UNION:
            member.offset = 0
        self.members.append(member)
    
    @property
    def targetsize(self) -> Optional[int]: return self._targetsize
    
    def print(self, *, pad:bool=PAD_DEFAULT, **kwargs):
        size = f'\n\t/*{self.size:x}*/' if self.size is not None else ''
        pack_begin = pack_end = ''
        if self.pack is not None:
            pack_begin = f'#pragma pack(push, {self.pack:d})\n'
            pack_end   = f'\n#pragma pack(pop)'
        text = f'{pack_begin}{self!s}\n{{\n' + '\n'.join(f'\t{m!r}' for m in self.members) + f'{size}\n}};{pack_end}'
        print(text, **kwargs)


class StructSymbol(BaseStructSymbol):

    def __init__(self, name:str, **kwargs):
        super().__init__(SymbolKind.STRUCT, name, **kwargs)
        
    def _evaluate(self, db:'SymbolDatabase') -> bool:
        members_eval = True
        ##DEBUG: always evaluate so that members get fully evaluated
        if self.has_size:
            # No size re-eval needed, but ensure that all members get fully evaluated
            members_eval = all(m.evaluate(db) for m in self.members)

        elif not self.has_size:
            size = 0
            pack = self.pack if self.pack else 4  # default pack
            for member in self.members:
                if not member.evaluate(db):
                    members_eval = False  # still keep going

                if not member.has_size:
                    return False  # can't evaluate

                
                # if minpack == 0 and member.typename != 'char[0]':
                #     print(repr(self), f'pack={pack}')
                #     print(repr(member), f'size={member.size}', f'basesize={member.basesize}')
                validzero = (member.basesize == 0 or member.typename == 'char[0]') # crappy hardcoded hacks GAHHHHH
                

                if member.basesize == 0 and not validzero:
                    print(repr(self), f'pack={pack}')
                    print(repr(member), f'size={member.size}', f'basesize={member.basesize}')

                    
                minpack = 0 if validzero else min((size % pack), (size % member.basesize))
                if minpack:
                    size += minpack - (size % minpack)

                member.offset = size
                size += member.size
                
                # if validzero or ((size % minpack) == 0) or (minpack == 1): # currently aligned to pack/member base size, just add member
                #     member.offset = size
                #     size += member.size
                # else: # pack alignment is performed based on an array element's type
                #     size += minpack - (size % minpack) # pad size to pack align
                #     member.offset = size
                #     size += member.size
                
                # elif (size // pack) != ((size + member.basesize) // pack): # pack alignment is performed based on an array element's type
                #     size += pack - (size % pack) # pad size to pack align
                #     member.offset = size
                #     size += member.size
                # else:
                #     member.offset = size
                #     size += member.size

            
            if (size % pack) != 0: # end struct and align to pack size
                size += pack - (size % pack) # pad size to pack align
            self._size = size

        ##DEBUG: testing
        return self.has_size and members_eval
        #return self.has_size
    
    def __repr__(self):
        pack = f' : pack({self.pack})' if self.pack else ''
        comment = f' // {self.comment}' if self.comment else ''
        return f'struct {self.display_name}{pack};{comment}'
    def __str__(self):
        comment = f' // {self.comment}' if self.comment else ''
        return f'struct {self.display_name}{comment}'


class UnionSymbol(BaseStructSymbol):

    def __init__(self, name:str, **kwargs):
        super().__init__(SymbolKind.UNION, name, **kwargs)
        
    def _evaluate(self, db:'SymbolDatabase') -> bool:
        members_eval = True
        ##DEBUG: always evaluate so that members get fully evaluated
        if self.has_size:
            # No size re-eval needed, but ensure that all members get fully evaluated
            members_eval = all(m.evaluate(db) for m in self.members)

        elif not self.has_size:
            size = 0
            pack = self.pack if self.pack else 4  # default pack
            for member in self.members:
                if not member.evaluate(db):
                    members_eval = False  # still keep going

                if not member.has_size:
                    return False  # can't evaluate

                size = max(size, member.size)

            
            if (size % pack) != 0: # end struct and align to pack size
                size += pack - (size % pack) # pad size to pack align
            self._size = size

        ##DEBUG: testing
        return self.has_size and members_eval
        #return self.has_size

    def __repr__(self):
        pack = f' : pack({self.pack})' if self.pack else ''
        comment = f' // {self.comment}' if self.comment else ''
        return f'union {self.display_name}{pack};{comment}'
    def __str__(self):
        comment = f' // {self.comment}' if self.comment else ''
        return f'union {self.display_name}{comment}'

#endregion


#######################################################################################

#region Tagged comment classification

# used to work around Ghidra's utter lack of helpful output

PARSE_TAGGED_COMMENT = re.compile(rf"""
    {WS1}* \[ (?P<taggedbody>[^ \] ]+) \] {WS1}* (?P<remaining>.*)
""", RE_FLAGS | re.VERBOSE)

PARSE_TAGGED_COMMENT_TYPE = re.compile(rf"""
    (?: (?P<module> [^ \]|: ]+ )
        |
    (?: (?P<keyword> class|struct|union|enum|flags ) : (?P<targetsize> {RE_UINTEGER} ) ) )
        |
    (?: type : (?P<typename> {RE_SYMBOL_TYPE} ) )
        |
    (?: pack : (?P<pack> {RE_UINTEGER} ) )
        |
    (?: tags : (?P<tags>.* ) )
        |
    (?: (?P<unknown> [^ : ]* ) : (?P<unknownbody> .* ) )
    """, RE_FLAGS | re.VERBOSE)


# define Python user-defined exceptions
class TaggedError(Exception):
    """Errors when parsing tagged comment helpers"""
    offset:Optional[int]
    comment:Optional[str]

    def __init__(self, *args, offset:Optional[int]=None, comment:Optional[str]=None, **kwargs):
        super().__init__(*args, **kwargs)
        self.offset = offset
        self.comment = comment

class TaggedDuplicateError(TaggedError):
    """A named tag or module appears more than once"""
    pass

class TaggedFormatError(TaggedError):
    """Bad formatting for tagged comment item"""
    pass


class TaggedComment(namedtuple('_TaggedComment', ('taggedbody', 'remaining', 'module', 'keyword', 'targetsize', 'typename', 'pack', 'tags', 'unknown'))):

    taggedbody:Optional[str]
    remaining:Optional[str]
    module:Optional[str]
    keyword:Optional[str]
    targetsize:Optional[int]
    typename:Optional[str]
    pack:Optional[int]
    tags:List[str]
    unknown:Dict[str,str]

    def __new__(cls, taggedbody:Optional[str]=None, remaining:Optional[str]=None, module:Optional[str]=None, keyword:Optional[str]=None, targetsize:Optional[int]=None, typename:Optional[str]=None, pack:Optional[int]=None, tags:Optional[List[str]]=None, unknown:Optional[Dict[str,str]]=None):

        if tags is None: tags = []
        if unknown is None: unknown = {}

        return super().__new__(cls, taggedbody=taggedbody, remaining=remaining, module=module, keyword=keyword, targetsize=targetsize, typename=typename, pack=pack, tags=tags, unknown=unknown)

    TAGGED_RESERVED = ('class', 'struct', 'union', 'enum', 'flags')
    TAGGED_GROUPS = ('module', 'keyword', 'typename', 'pack', 'tags', 'unknown')

    @classmethod
    def _parse_tagged(cls, comment:str, dic:dict, m:Match, offset:int, key:str, value:str) -> None:
        getattr(cls, f'_parse_tagged_{key}')(comment, dic, m, offset, key, value)
    
    @classmethod
    def _parse_tagged_module(cls, comment:str, dic:dict, m:Match, offset:int, key:str, value:str) -> None:
        dic[key] = value
    
    @classmethod
    def _parse_tagged_keyword(cls, comment:str, dic:dict, m:Match, offset:int, key:str, value:str) -> None:
        dic[key] = value
        dic['targetsize'] = int(m['targetsize'], 0)

    @classmethod
    def _parse_tagged_typename(cls, comment:str, dic:dict, m:Match, offset:int, key:str, value:str) -> None:
        dic[key] = value

    @classmethod
    def _parse_tagged_pack(cls, comment:str, dic:dict, m:Match, offset:int, key:str, value:str) -> None:
        dic[key] = int(value, 0)

    @classmethod
    def _parse_tagged_unknown(cls, comment:str, dic:dict, m:Match, offset:int, key:str, value:str) -> None:
        #value = value.strip()  # don't strip, since the patterns don't check elsewhere
        if not value:
            raise TaggedFormatError(f'Empty tagged type name', offset=offset, comment=comment)
        if value in cls.TAGGED_RESERVED:
            raise TaggedFormatError(f'Failed to match special tagged type {value!r}', offset=offset, comment=comment)
        if value in dic.get(key, {}):
            raise TaggedDuplicateError(f'Unknown tagged type {value!r} already exists', offset=offset, comment=comment)
        dic.setdefault(key, {})[value] = m['unknownbody']
        
    @classmethod
    def _parse_tagged_tags(cls, comment:str, dic:dict, m:Match, offset:int, key:str, value:str) -> None:
        dic[key] = tags = []
        if not value:
            return # no handling for empty tags
        
        for t in value.split(','):
            if t in tags: # could be warning (or ignored)
                raise TaggedDuplicateError(f'Tags name {value!r} already exists', offset=offset, comment=comment)
            tags.append(t)
        

    @classmethod
    def parse(cls, comment:str) -> 'TaggedComment':
        comment = (comment or '').strip()

        m1 = PARSE_TAGGED_COMMENT.fullmatch(comment)
        if not m1:
            return cls(taggedbody=None, remaining=comment)

        taggedbody, remaining = m1['taggedbody'], m1['remaining']

        dic = {}
        for s in taggedbody.split('|'):
            s = s.strip()
            if not s: raise TaggedFormatError(f'Empty tagged item {s!r}', comment=comment)
            if s.__class__ is not str:
                print(f'WRONG TYPE: {s.__class__.__name__}')
            m2 = PARSE_TAGGED_COMMENT_TYPE.fullmatch(s)
            if not m2: raise TaggedFormatError(f'Unexpected tagged item format {s!r}', comment=comment)

            key = ([k for k in cls.TAGGED_GROUPS if m2[k] is not None] or (None,))[0]
            
            if key != 'unknown' and key in dic:  # unknown has its own handling for this
                raise TaggedDuplicateError(f'Tagged type name {key!r} already exists', offset=m2.span(0), comment=comment)

            # call one of the predefined tagged function names
            getattr(cls, f'_parse_tagged_{key}')(comment, dic, m2, offset=m2.span(0), key=key, value=m2[key])
            #cls._parse_tagged(comment, dic, m2, offset=m2.span(0), key=key, value=m2[key])

        return cls(taggedbody=taggedbody, remaining=remaining, **dic)

#endregion


#######################################################################################

#region Parser classes

# define Python user-defined exceptions
class ParserError(Exception):
    """Errors when parsing a file"""
    filename:Optional[str]
    filetext:Optional[str]
    linenumber:Optional[int]
    index:Optional[int]

    offset:Optional[int]

    def __init__(self, *args, filename:Optional[str]=None, filetext:Optional[str]=None, linenumber:Optional[int]=None, index:Optional[int]=None, offset:Optional[int]=None, **kwargs):
        super().__init__(*args, **kwargs)
        self.filename = filename
        self.filetext = filetext
        self.linenumber = linenumber
        self.index = index
        self.offset = offset


class BaseParser:
    filename:Optional[str]
    filetext:Optional[str]
    linenumber:Optional[int]
    index:Optional[int]

    def __init__(self):
        self.filename = None
        self.filetext = None
        self.linenumber = None
        self.index = None

    def error(self, *args, offset:Optional[int]=None, **kwargs):
        #TODO: Do a better job with index and linenumber
        error_cls = ParserError
        if args and args[0] is type:
            error_cls, args = args[0], args[1:]
        
        raise error_cls(*args, filename=self.filename, filetext=self.filetext, linenumber=self.linenumber, index=self.index, offset=offset, **kwargs)


class HeaderParser(BaseParser):
    db:'SymbolDatabase'
    def __init__(self, db:'SymbolDatabase'):
        super().__init__()
        self.db = db

    def parsefile(self, filename:str, encoding:str='utf-8', **kwargs):
        with open(filename, 'rt', encoding=encoding) as reader:
            filetext = reader.read()
        
        return self.parse(filetext, filename=filename, **kwargs)


    def parse(self, filetext:str, *, filename:Optional[str]=None, preprocessor:bool=True, functions:bool=True, **kwargs):
        self.filename = filename
        self.filetext = filetext
        
        text = filetext # modified and used as the parsed text

        # prepare for parsing, fix Ghidra's crap
        text = sub_crlf2lf(text)
        text = sub_spaces4tabs(text)
        text = sub_float10(text)
        text = sub_compact_field0x(text)
        text = rem_ctypedef(text)
        if not preprocessor:
            text = rem_define(text)

        # only simple defines
        if preprocessor:
            self.parse_defines(text, **kwargs)

        # parse typedefs and blocks (struct,enum,union)
        self.parse_typedefs(text, **kwargs)
        self.parse_blocks(text, **kwargs)

        # parse function declarations
        if functions:
            self.parse_functions(text, **kwargs)

    
    def parse_tagged_comment(self, comment:str) -> TaggedComment:
        return TaggedComment.parse(comment)
    
    def parse_defines(self, text:str, **kwargs) -> None:
        for m in PARSE_PREPROCESSOR.finditer(text):
            preprocessor = m['preprocessor']
            if preprocessor == 'undef':
                self.error(f'Preprocessor #undef not supported: {m[0]}')
            elif preprocessor != 'define':
                continue  # not handled
            
            name        = m['name']
            is_function = m['arguments'] is not None
            typename    = m['typename']
            value       = m['value']
            comment     = m['comment'] or None

            if is_function:
                self.error(f'Macro functions not supported: {m[0]}')
            if name is None:
                self.error(f'Failed to parse define name: {m[0]}')
            
            if typename is not None:
                self.db.add_define(DefineTypedefSymbol(name, typename, comment=comment, **kwargs))
            elif value is not None:
                self.db.add_define(DefineValueSymbol(name, int(value, 0), comment=comment, **kwargs))
            else:
                self.error(f'Failed to parse define typename or value: {m[0]}')

    def parse_typedefs(self, text:str, **kwargs) -> None:
        for m in PARSE_TYPEDEF.finditer(text):
            name        = m['name']
            decl        = m['decl'] or None
            is_function = m['arguments'] is not None

            if is_function:
                if name not in EXCLUDE_FUNCTYPEDEFS:
                    ##HACK: only __cdecl function typedefs are defined for OpenLRR,
                    ##      and ghidra doesn't display calling conventions on function typedefs...
                    if decl is None: decl = '__cdecl'

                hide = name in EXCLUDE_FUNCTYPEDEFS
            else:
                hide = name not in ALLOWED_TYPEDEFS

            self.db.add(self.parse_symbol_type(TypedefSymbol, m, hide=hide, nocomment=True, default_decl=decl, **kwargs))

    def parse_functions(self, text:str, **kwargs) -> None:
        for m in PARSE_FUNCTION_HEADER.finditer(text):
            name        = m['name']
            decl        = m['decl'] or None

            ##HACK: Ghidra does not display __stdcall calling conventions for functions.
            ##      Assume all missing decls are __stdcall.
            if decl is None: decl = '__stdcall'

            hide = name.startswith('__')  # helper prefixed attached to all useless internal C runtime functions

            self.db.add(self.parse_symbol_type(FunctionSymbol, m, hide=hide, nocomment=True, default_decl=decl, **kwargs))

    def parse_blocks(self, text:str, **kwargs) -> None: # -> Iterable[Symbol]:
        for m in PARSE_TYPE_BLOCK.finditer(text):
            name    = m['name']
            typedef = m['typedef'] or None

            symbol = self.parse_block(m, **kwargs)
            self.db.add(symbol)
            if typedef and typedef != name:  # don't typedef yourself
                self.db.add(TypedefSymbol(typedef, name, parent=symbol, **kwargs))
                # self.db.add_typedef(typedef, name)


    def parse_block(self, m:Match, **kwargs) -> Symbol:
        keyword, typedef, name, comment, textbody = m.group('keyword', 'typedef', 'name', 'comment', 'textbody')
        comment = (comment or '').strip() or None

        t = self.parse_tagged_comment(comment)
        hide = t.taggedbody is None

        if keyword == 'enum':
            symbol_cls = FlagsSymbol if (t.keyword and t.keyword == 'flags') else EnumSymbol

            ## OPTIONAL: replace comment=comment with comment=t.remaining  for untagged half of comments
            symbol = symbol_cls(name, typename=t.typename, targetsize=t.targetsize, comment=comment or None, hide=hide, tagged=t, **kwargs)
            for value in self.parse_enum_values(ValueSymbol, textbody, **kwargs):
                symbol.add_value(value)
            if ENUM_SORT_DEFAULT:
                symbol.sort_values()  # numerical-sort enums by default
        else:
            # class and struct have no handling difference at the moment
            symbol_cls = UnionSymbol if keyword == 'union' else StructSymbol
            
            ## OPTIONAL: replace comment=comment with comment=t.remaining  for untagged half of comments
            symbol = symbol_cls(name, targetsize=t.targetsize, pack=t.pack, comment=comment or None, hide=hide, tagged=t, **kwargs)
            for member in self.parse_block_members(MemberSymbol, textbody, **kwargs):
                symbol.add_member(member)
        
        # self.db.add(symbol)
        return symbol
    
    def parse_symbol_value(self, symbol_cls:Type[ValueSymbol], m:Match, nocomment:bool=False, **kwargs) -> ValueSymbol:
        name    = m['name']
        value   = int(m['value'], 0)
        comment = m['comment'] or None

        return symbol_cls(name, value, comment=comment, **kwargs)
            
    def parse_enum_values(self, symbol_cls:Type[ValueSymbol], text:str, **kwargs) -> List[ValueSymbol]:
        text = text.strip()
        values = []

        for s in text.split('\n'):
            s = s.strip()
            if not s: continue  # ignore empty lines

            m2 = PARSE_ENUMVALUE.fullmatch(s)
            if not m2: self.error(f'BAD MEMBER: {s}')
            values.append(self.parse_symbol_value(symbol_cls, m2, nocomment=True, **kwargs))
        
        return values
    
    def parse_block_members(self, symbol_cls:Type[TypeSymbol], text:str, **kwargs) -> List[MemberSymbol]:
        text = text.strip() #m['textbody'].strip()
        members = []

        for s in text.split('\n'):
            s = s.strip()
            if not s: continue  # ignore empty lines

            m2 = PARSE_MEMBER.fullmatch(s)
            if not m2: self.error(f'BAD MEMBER: {s}')
            members.append(self.parse_symbol_type(symbol_cls, m2, nocomment=False, **kwargs))
        
        return members

    def parse_type_arguments(self, symbol_cls:Type[TypeSymbol], text:str, **kwargs) -> List[TypeSymbol]:
        text = text.strip()
        if text in ('','void','VOID'): return [] # special case for (void) empty arguments

        args = []

        arguments = text
        while arguments:  # loop will continue until arguments is entirely stripped
            arguments = arguments.lstrip()
            m = PARSE_PARAM.match(arguments)

            #realoffset = len(text)-len(arguments)
            if not m:
                self.error(f'BAD arguments state: {arguments!r}')
            
            ##HACK: Special handling for ellipsis, which doesn't match any other groups
            is_ellipsis = m['ellipsis'] is not None
            if is_ellipsis:
                args.append(symbol_cls(None, '...', **kwargs))
            else:
                args.append(self.parse_symbol_type(symbol_cls, m, nocomment=True, **kwargs))

            arguments = arguments[m.span(0)[1]:].lstrip()
            if arguments:
                if is_ellipsis:
                    self.error(f'BAD end of arguments, nothing should be after ellipsis {"..."!r}: {arguments}')
                elif arguments[0] == ',':
                    arguments = arguments[1:] #.lstrip()  # strip commma
                    if not arguments:
                        self.error(f'BAD end of arguments, nothing after comma: {arguments}')
                else:
                    self.error(f'BAD end of arguments, expected comma: {arguments}')

        return args

    def _parse_ptr_counts(self, text:str) -> int:
        # key is used because both pointers attached to the name, and attached to the type,
        #  which can be both for function typedefs, etc.
        return (text or '').count('*')

    def _parse_array_counts(self, text:str) -> Tuple[int,...]:
        if text is None: return ()  # no arrays matched, return empty tuple
        
        arrays = []

        #NOTE: this should never have any failures, so we can safely use finditer
        for m2 in PARSE_ARRAYCOUNT.finditer(text):
            arrays.append(int(m2['count'], 0))

        return tuple(arrays)

    # def _parse_is_function(self, text:str) -> bool:
    #     return bool(text)  # no arguments match, must not be a function

    def parse_symbol_type(self, symbol_cls:Type[TypeSymbol], m:Match, nocomment:bool=False, default_decl:Optional[str]=None, **kwargs) -> TypeSymbol:
        typename    = m['typename']
        name        = m['name']      or None
        namespace   = m['namespace'] or None
        modifier    = m['modifier']  or None
        decl        = m['decl']      or default_decl
        typeptrs    = self._parse_ptr_counts(m['typeptrs'])
        nameptrs    = self._parse_ptr_counts(m['nameptrs'])
        arrays      = self._parse_array_counts(m['arrays'])
        is_function = m['arguments'] is not None
        comment     = None if nocomment else (m['comment'] or None)

        symbol = symbol_cls(name, typename, modifier=modifier, decl=decl, typeptrs=typeptrs, nameptrs=nameptrs, arrays=arrays, is_function=is_function, comment=comment, namespace=namespace, **kwargs)

        if is_function:
            # arguments[1:-1] to strip surrounding '(' ')' braces
            for arg in self.parse_type_arguments(ParamSymbol, m['arguments'][1:-1], **kwargs):
                symbol.add_argument(arg) #, **kwargs)

        return symbol

class AsciiParser(HeaderParser):
    
    def parse(self, filetext:str, *, filename:Optional[str]=None, functions:bool=True, merge_functions:bool=True, doglobals:bool=True, guids:bool=False, cstrings:bool=False, cfloating:bool=False, **kwargs):
        self.filename = filename
        # probably best to enforce this, due to the massive size of these files...
        filetext = rem_trimlines(filetext)
        self.filetext = filetext
        
        text = filetext # modified and used as the parsed text

        # prepare for parsing, fix Ghidra's crap

        #text = rem_trimlines(text) # (performed above)
        text = rem_undefinedbytes(text)

        textf,textg = split_functionglobalspans(text)

        # parse global variables and addresses
        if doglobals:
            if textg is None:
                self.error('Failed to split globals')
            
            if cstrings:
                self.error('cstrings not supported yet!')
            textg = rem_globalcstring(textg)

            if cfloating:
                self.error('cfloating not supported yet!')
            textg = rem_constfloating(textg)

            if guids:
                self.parse_global_guids(textg, **kwargs)
            textg = PARSE_GLOBALGUID.sub("", textg)

            self.parse_global_vars(textg, **kwargs)
            textg = PARSE_GLOBALVAR_ALL.sub("", textg)

            # textg = rem_undefinedbytes(textg)

        # parse function addresses
        if functions:
            if textf is None:
                self.error('Failed to split function')
            self.parse_functions(textf, merge_functions=merge_functions, **kwargs)
    
    def parse_global_vars(self, text:str, **kwargs) -> None:
        for m in PARSE_GLOBALVAR_ALL.finditer(text):
            address   = int(m['address'], 16)
            typename  = m['typename']
            name      = m['name']
            typeptrs  = self._parse_ptr_counts(m['typeptrs'])
            arrays    = self._parse_array_counts(m['arrays'])

            value_raw = m['value_raw'] or None
            if value_raw is not None and value_raw in ('??', 'NaP'):
                value_raw = None

            self.db.add(VariableSymbol(name, typename, value_raw=value_raw, address=address, typeptrs=typeptrs, arrays=arrays))

        # #PARSE_GLOBALVAR_ORDERS = (PARSE_GLOBALVAR_QQ, PARSE_GLOBALVAR_VALUE, PARSE_GLOBALVAR_EMPTY)
        # PARSE_GLOBALVAR_ORDERS = (PARSE_GLOBALVAR_VALUE, PARSE_GLOBALVAR_EMPTY)
        # for i,PARSE in enumerate(PARSE_GLOBALVAR_ORDERS):
        #     for m in PARSE.finditer(text):
        #         address   = int(m['address'], 16)
        #         typename  = m['typename']
        #         name      = m['name']
        #         typeptrs  = self._parse_ptr_counts(m['typeptrs'])
        #         arrays    = self._parse_array_counts(m['arrays'])

        #         value_raw = m['value_raw'] if (PARSE is PARSE_GLOBALVAR_VALUE) else None
        #         if value_raw is not None and value_raw in ('??', 'NaP'):
        #             value_raw = None

        #         self.db.add(VariableSymbol(name, typename, value_raw=value_raw, address=address, typeptrs=typeptrs, arrays=arrays))
        #     # remove <GLOBALS>
        #     #text2 = PARSE.sub("", text2)
    
    def parse_global_guids(self, text:str, **kwargs) -> None:
        for m in PARSE_GLOBALGUID.finditer(text):
            address   = int(m['address'], 16)
            typename  = m['typename']
            name      = m['name']
            
            value     = m['value']
            value_raw = m['value_raw']

            comment   = '[???|tags:IDL]'
            tagged    = self.parse_tagged_comment(comment)

            self.db.add(VariableSymbol(name, typename, value=value, value_raw=value_raw, address=address, comment=comment, tagged=tagged))

    def parse_functions(self, text:str, *, merge_functions:bool=True, **kwargs) -> None:
        count = 0
        for m in PARSE_FUNCTION_ASCII.finditer(text):
            address   = int(m['address'], 16)
            function  = m['function']
            
            m1 = re.match(r"^[^\(]+[ *](?P<name>[^ *\(]+)+\(", function)
            if not m1: self.error(f'Failed to parse name of function {len(count)}: {function!r}')
            name      = m1['name']

            ##HACK: Skip over this garbage (don't even count it)
            if name.startswith('Unwind@'):
                continue

            m2 = PARSE_FUNCTION_HEADER.match(function + ';')
            if not m2 and name.startswith('__'):
                # Ignore those nasty std internal functions with arguments such as: undefined1[12] param_1.
                count += 1
                continue
            elif not m2:
                self.error(f'Failed to parse function {count}: {function!r}')
            name      = m2['name']
            decl      = m2['decl'] or None

            ##HACK: Ghidra does not display any calling conventions for functions in ascii.
            ##      Assume all missing decls are __cdecl.
            ##      Since we can list the number of __stdcall's on one or two hands.
            if decl is None: decl = '__cdecl'

            hide = name.startswith('__')  # helper prefixed attached to all useless internal C runtime functions

            if merge_functions and name in self.db.symbols:
                symbol = self.db[name]
                if symbol.address is not None:
                    pass # not fully expected, but possibly not an error depending on the scenario
                else:
                    symbol.address = address # add address to previously parsed header function
            else:
                try:
                    # Doesn't exist, add it ourselves
                    self.db.add(self.parse_symbol_type(FunctionSymbol, m2, hide=hide, nocomment=True, default_decl=decl, address=address, **kwargs))
                except Exception as ex:
                    if name.startswith('__'):
                        # Ignore those nasty std internal functions with arguments such as: undefined1[12] param_1.
                        pass
                    else:
                        raise ex

            count += 1

        #     decl        = m['decl'] or None
        #     if not [d for d in ('__cdecl', '__stdcall', '__fastcall', '__thiscall') if d in functxt]:
        #         # No calling convention, enforce __cdecl because
        #         #  we can list the number of stdcalls on one or two hands.
        #         decl_orig = decl
        #         decl = '__cdecl '

        #     count += 1

        #     ##HACK: Ghidra does not display __stdcall calling conventions for functions.
        #     ##      Assume all missing decls are __stdcall.
        #     if decl is None: decl = '__stdcall'

        #     hide = name.startswith('__')  # helper prefixed attached to all useless internal C runtime functions

        #     self.db.add(self.parse_symbol_type(FunctionSymbol, m, hide=hide, nocomment=True, default_decl=decl, **kwargs))
        # for fn in list(RE_TXT_FUNCTIONS.finditer(txt_g)):
        #     address = int(fn['address'],16)
        #     functxt = fn['function']
        #     m = re.match(r"^[^\(]+[ ](?P<name>[^\(]+)+\(", functxt)
        #     if not m: raise ValueError(f'failed to find func {len(func_list)} name from: {functxt!r}')
        #     name = m['name']
        #     namespan = m.span("name")
        #     if name.startswith('__'):
        #         # skip double-underscore C runtime names
        #         continue
        #     #
        #     decl = ''
        #     if not [d for d in ('__cdecl', '__stdcall', '__fastcall', '__thiscall') if d in functxt]:
        #         # No calling convention, enforce __cdecl because
        #         #  we can list the number of stdcalls on one or two hands.
        #         decl_orig = decl
        #         decl = '__cdecl '
        #     # HARDCODED HANDLING
        #     if name in addr_map:
        #         name_orig = name
        #         name = DUPLICATE_NAMES[name]
        #     #
        #     functxt_orig = functxt
        #     # print(functxt)
        #     # print(namespan)
        #     # DEBUG_i += 1
        #     # if DEBUG_i == 20:
        #     #     raise ValueError('DEBUG stop')
        #     # print(f'{functxt_orig[:namespan[0]]}', '||||', f'{functxt_orig[namespan[1]:]}')
        #     # replace calling convention and/or duplicate name
        #     functxt = f'{functxt_orig[:namespan[0]]}{decl}{name}{functxt_orig[namespan[1]:]}'
        #     #
        #     func_list.append((address, name, functxt))
        #     functxt_list.append(functxt)
        #     addr_map[name] = address
        # functions = '\n'.join(f'{fn};' for fn in functxt_list)
        # return functions, func_list, addr_map


#endregion


#######################################################################################

#region Symbols database

class SymbolDatabase:
    symbols:Dict[str,Symbol]
    defines:Dict[str,Symbol]  # very simple defines dict that only evaluates directly to a symbol or value (the later of which is unused)
    convert_defines:bool
    ##HACK: Awkward way of handling ellipsis '...' arguments without rewrites
    ellipsis:PrimitiveSymbol

    def __init__(self, symbols:Optional[Dict[str,Symbol]]=None, defines:Optional[Dict[str,Symbol]]=None, convert_defines:bool=True): #*args, **kwargs):
        self.symbols = dict(symbols) if symbols is not None else {}
        self.defines = dict(defines) if defines is not None else {}
        self.convert_defines = bool(convert_defines)
        self.ellipsis = PrimitiveSymbol('...', 0,  evaled=True, hide=True)

    def add(self, symbol:Symbol) -> bool:
        define = self.get_define(symbol.name, None)
        if define is not None:
            raise ValueError(f'Symbol name overwritten by define {define.name!r}, parser cannot handle this')
        return self.add_symbol(symbol)

    def get(self, key:str, default:Any=None, *, allow_ellipsis:bool=False) -> Optional[Symbol]:
        if isinstance(key, Symbol): key = key.name

        define = self.get_define(key, None)
        if define is not None:
            if self.convert_defines and isinstance(define, DefineTypedefSymbol):
                symbol = self.get_symbol(define.typename, None, allow_ellipsis=allow_ellipsis)
                if symbol is None:
                    raise ValueError(f'Unexpected failed to convert define typename {define.name} for: {define}')
                return symbol
            return define
        return self.get_symbol(key, default, allow_ellipsis=allow_ellipsis)


    def add_symbol(self, symbol:Symbol) -> bool:
        orig = self.symbols.setdefault(symbol.name, symbol)
        if orig is not symbol:
            if isinstance(orig, TypeSymbol) and isinstance(symbol, (BaseStructSymbol, BaseEnumSymbol)):
                self.symbols[symbol.name] = symbol  # override redudant typedefs
                return True
            ##DEBUG:
            elif not isinstance(symbol, TypedefSymbol):
                print(f'[Duplicate]: {symbol.name}\n old: {orig}\n new: {symbol}')
        return orig is symbol

    def get_symbol(self, key:str, default:Any=None, *, allow_ellipsis:bool=False) -> Optional[Symbol]:
        if isinstance(key, Symbol): key = key.name

        if allow_ellipsis and key == self.ellipsis.name:
            return self.ellipsis
        
        return self.symbols.get(key, default)


    def add_define(self, define:Symbol) -> bool:
        orig = self.defines.setdefault(define.name, define)
        if orig != define:
            raise ValueError(f'Duplicate define for {define.name!r}, parser cannot handle this')
        return orig is define

    def get_define(self, key:str, default:Any=None) -> Optional[Symbol]:
        if isinstance(key, Symbol): key = key.name
        return self.defines.get(key, default)


    def get_ellipsis(self, key:str, default:Any=None) -> Optional[PrimitiveSymbol]:
        return self.ellipsis if key == self.ellipsis.name else default


    def __len__(self) -> int:
        return len(self.symbols)
    def __iter__(self) -> Iterator[str]:
        return iter(self.symbols)
    def keys(self) -> Iterator[str]:
        return self.symbols.keys()
    def values(self) -> Iterator[Symbol]:
        return self.symbols.values()
    def items(self) -> Iterator[Tuple[str,Symbol]]:
        return self.symbols.items()
    def __contains__(self, key:Union[str,Symbol]) -> bool:
        if isinstance(key, Symbol): key = key.name
        return key in self.symbols
    
    def __getitem__(self, key:Union[str,Symbol]) -> Symbol:
        if isinstance(key, Symbol): key = key.name
        return self.symbols[key]
    def __setitem__(self, key:Union[str,Symbol], symbol:Symbol) -> Symbol:
        if isinstance(key, Symbol): key = key.name
        self.symbols[key] = symbol
    def __delitem__(self, key:Union[str,Symbol]) -> None:
        if isinstance(key, Symbol): key = key.name
        del self.symbols[key]
            
    def add_primitive(self, name:str, size:int, *, prefixes:List[str]=(), postfixes:List[str]=(), evaled:bool=True, hide:bool=True) -> None:
        if not prefixes: prefixes = ('',)
        if not postfixes: postfixes = ('',)
        for pre in prefixes:
            for post in postfixes:
                pname = pre + name + post
                self.add(PrimitiveSymbol(pname, size, evaled=evaled, hide=hide))

    def add_typedef(self, name:str, typename:str, *, pointers:int=0, arrays:List[int]=(), prefixes:List[str]=(), postfixes:List[str]=(), hide:bool=True) -> None:
        if not prefixes: prefixes = ('',)
        if not postfixes: postfixes = ('',)
        for pre in prefixes:
            for post in postfixes:
                pname = pre + name + post
                self.add(TypedefSymbol(pname, typename, typeptrs=pointers, arrays=arrays, hide=hide))

    def add_wintype(self, name:str, typename:str, prefixes:List[str]=(), postfixes:List[str]=(), *, ptr:Optional[str]='LP', hide:bool=True) -> None:
        if not prefixes: prefixes = ('',)
        if not postfixes: postfixes = ('',)
        for pre in prefixes:
            for post in postfixes:
                pname = pre + name + post
                self.add(TypedefSymbol(pname, typename, hide=hide))
                if ptr is not None:
                    self.add(TypedefSymbol(ptr + pname, pname, typeptrs=1, hide=hide))

    def add_interface(self, name:str, prefixes:List[str]=(), postfixes:List[str]=(), *, ptr:Optional[str]='LP', hide:bool=True) -> None:
        if not prefixes: prefixes = ('',)
        if not postfixes: postfixes = ('',)
        for pre in prefixes:
            for post in postfixes:
                pname = pre + name + post
                self.add(TypedefSymbol(pname, 'IUnknown', hide=hide))
                if ptr is not None:
                    # pname[1:] to strip 'I' from interface pointer name
                    self.add(TypedefSymbol(ptr + pname[1:].upper(), pname, typeptrs=1, hide=hide))

    def override_display_name(self, key:Union[str,Symbol], display_name:str, *, optional:bool=False) -> None:
        """This should be called after db.include_header*()"""
        if isinstance(key, Symbol):
            key.display_name = display_name
        # when optional, do nothing if key isn't defined in symbols
        elif not optional or key in self.symbols:
            # self.symbols[key]._display_name = display_name
            self.symbols[key].display_name = display_name
    
    def hide_symbol(self, key:Union[str,Symbol], hide:bool=True, *, optional:bool=False) -> None:
        if isinstance(key, Symbol):
            key.hide = hide
        # when optional, do nothing if key isn't defined in symbols
        elif not optional or key in self.symbols:
            self.symbols[key].hide = hide


    def include_headerfile(self, filename:str, encoding:str='utf-8', evaluate:bool=True, **kwargs) -> bool:
        with open(filename, 'rt', encoding=encoding) as reader:
            filetext = reader.read()
        
        return self.include_header(filetext, filename=filename, evaluate=evaluate, **kwargs)
        
    def include_header(self, filetext:str, *, filename:Optional[str]=None, evaluate:bool=True, **kwargs) -> bool:
        parser = HeaderParser(self)

        parser.parse(filetext, filename=filename, **kwargs)

        if evaluate:
            return self.evaluate_all()
        else:
            return True


    def include_asciifile(self, filename:str, encoding:str='utf-8', evaluate:bool=True, **kwargs) -> bool:
        with open(filename, 'rt', encoding=encoding) as reader:
            filetext = reader.read()
        
        return self.include_ascii(filetext, filename=filename, evaluate=evaluate, **kwargs)
        
    def include_ascii(self, filetext:str, *, filename:Optional[str]=None, evaluate:bool=True, **kwargs) -> bool:
        parser = AsciiParser(self)

        parser.parse(filetext, filename=filename, **kwargs)

        if evaluate:
            return self.evaluate_all()
        else:
            return True
        
    def evaluate_all(self, **kwargs) -> bool:
        return self._evaluate_all(**kwargs)
        
    def _evaluate_all(self, **kwargs) -> bool:
        # lazy auto-evaluation for Ellipsis
        self.ellipsis.evaluate(self)

        # Lazily iterate through the list of symbols and evaluate everything as we go.
        #  any symbol that says it failed will be evaluated in the next pass, and so on.
        #
        # Symbol.evaluate(db) SHOULD NEVER call another Symbol.evaluate!!
        #  This is what the pass system is handled for to avoid any awkward cyclic redundancy.
        #
        # Symbol.evaluate(db) may return false even if it can be used by other types.
        # Evaluation requires all Symbol links to function,
        #  while many symbols only need to know their size to function.
        #  Use the Symbol.has_size property to determine if you have what you need
        remaining = list(self.defines.values()) + list(self.symbols.values())
        total = len(remaining)
        last_pass = -1
        passes = 0
        while remaining and last_pass != 0:
            last_pass = 0
            remaining_next = []
            for r in remaining:
                if r.evaluate(self):
                    last_pass += 1
                else:
                    remaining_next.append(r)
            remaining = remaining_next
            passes += 1
        
        if last_pass == 0 or remaining:
            print(f'Failed to evaluate all tokens. Completed {total-len(remaining)}/{total} within {passes} passes')
            print(f'last_pass = {last_pass}')
            SCRIPT_DIR:str = os.path.abspath(os.path.dirname(__file__))
            print(SCRIPT_DIR)
            with open(os.path.join(SCRIPT_DIR, 'ghidra_export.log'), 'wt+', encoding='utf-8') as f:
                for r in remaining:
                    f.write(repr(r) + '\n')
                f.flush()
            return False

        else:
            print(f'All symbols successfully evaluated within {passes} passes')
            return True


    def failed_targets(self):
        print(*[repr(s) for s in self.values() if s.has_size and hasattr(s,'targetsize') and s.targetsize is not None and s.size != s.targetsize],sep='\n')

    def populate_primitives(self):
        self.add_primitive('void',      0)

        self.add_primitive('char',      1, prefixes=('', 'signed ', 'unsigned '))
        self.add_primitive('short',     2, prefixes=('', 'signed ', 'unsigned '), postfixes=('', ' int'))

        self.add_primitive('signed',    4)
        self.add_primitive('unsigned',  4)
        self.add_primitive('int',       4, prefixes=('', 'signed ', 'unsigned '))

        self.add_primitive('long',      4, prefixes=('', 'signed ', 'unsigned '), postfixes=('', ' int'))
        self.add_primitive('long long', 8, prefixes=('', 'signed ', 'unsigned '), postfixes=('', ' int'))

        self.add_primitive('float',     4)
        self.add_primitive('double',    8)
        self.add_primitive('long double', 10)

        ##NOTE: Ghidra *does* have a typedef for these, but there's also no need to rely on them
        self.add_primitive('bool',      1)
        self.add_primitive('wchar_t',   2)
        self.add_primitive('size_t',    4)
        self.add_primitive('ptrdiff_t', 4)

        # existing typedef
        self.add_typedef('va_list', 'char', pointers=1)

class LegoRRSymbolDatabase(SymbolDatabase):
    ALLOWED_TYPEDEFS = {'Mesh_TextureStateChangeData', 'Mesh_Texture', 'Material', 'Animation_t', 'Movie_t', 'Material_t'}
    EXCLUDE_FUNCTYPEDEFS = {'QsortCompare', 'PTOP_LEVEL_EXCEPTION_FILTER', '_PNH', 'WNDPROC', 'DLGPROC', 'MMIOPROC', 'FARPROC'}

    def hide_typedefs(self, hide:bool=..., namelist:List[str]=...) -> None:
        if hide is Ellipsis and namelist is Ellipsis:
            hide, namelist = False, self.ALLOWED_TYPEDEFS
        
        hide = bool(hide)
        for typedef in (s for s in self.symbols if isinstance(s, TypedefSymbol) and not s.is_function):
            typedef.hide = ((typedef.name in namelist) == hide)

    def hide_funcdefs(self, hide:bool=..., namelist:List[str]=...) -> None:
        if hide is Ellipsis and namelist is Ellipsis:
            hide, namelist = True, self.EXCLUDE_FUNCTYPEDEFS
        
        hide = bool(hide)
        for typedef in (s for s in self.symbols if isinstance(s, TypedefSymbol) and s.is_function):
            typedef.hide = ((typedef.name in namelist) == hide)
    
    def hide_untagged(self, hide:bool) -> None:
        """Hide structs, unions, and enums without a tagged comment classification"""
        for symbol in (s for s in self.symbols if isinstance(s, (BaseStructSymbol, BaseEnumSymbol))):
            if symbol.tagged is None:
                symbol.hide = hide
    
    def populate_ghidra_primitives(self, *, preprocessor:bool=False):
        """preprocessor will include typedefs for required preprocessor defined symbols"""
        if not self.symbols:
            # if empty, we need to populate base primitives
            self.populate_primitives()

        # existing typedef
        #self.add_typedef('va_list', 'char', pointers=1)

        if not preprocessor:
            # handled by basic #define preprocessor, but can be removed if its acting up
            self.add_typedef('code',    'void')
        
        self.add_typedef('pointer',   'void', pointers=1)
        self.add_typedef('pointer32', 'void', pointers=1)

        # edge case for more stupid ghidra shenanigans
        self.add_typedef('char[0]',   'void')
        # self.add_typedef('float10',   'long double')  # transformed by HeaderParser into valid typedef

        # fix Ghidra being a butt for the millionth time. WHY IN THE WORLD IS THIS TYPEDEF'ED AS 8 BYTES!????
        self.add_primitive('GUID', 16, evaled=True, hide=True)
        
        self.add_typedef('addr', 'void', pointers=1, hide=False)
        self.add_typedef('ddw',  'uint', hide=False)

        # I'm not sure how to best-deal with these Ghidra types.
        self.add_typedef('ds',   'char', pointers=1, hide=True)
        self.add_typedef('unicode', 'wchar_t', pointers=1, hide=True)
        self.add_typedef('db',   'byte', pointers=1, hide=True)
        # self.add_typedef('ds',   'char', arrays=[1], hide=True)
        # self.add_typedef('db',   'byte', arrays=[1], hide=True)
    
    def override_openlrr_display_names(self, *, optional:Optional[bool]=None) -> None:
        self.override_display_name('byte',   'uint8',  optional=optional)
        self.override_display_name('short',  'sint16', optional=optional)
        self.override_display_name('ushort', 'uint16', optional=optional)
        self.override_display_name('int',    'sint32', optional=optional)
        self.override_display_name('uint',   'uint32', optional=optional)
        self.override_display_name('long',   'sint32', optional=optional)
        self.override_display_name('ulong',  'uint32', optional=optional)
        self.override_display_name('longlong',  'sint64')
        self.override_display_name('ulonglong', 'uint64')
        self.override_display_name('size_t', 'uint32', optional=optional)
        self.override_display_name('float',  'real32', optional=optional)
        self.override_display_name('BOOL',   'bool32', optional=optional)
        
        optional_true = True if optional is None else optional
        self.override_display_name('BOOL3',  'BoolTri', optional=optional_true)
        self.override_display_name('ImageBMP', 'Image', optional=optional_true)
        self.override_display_name('ImageFont', 'Font', optional=optional_true)
        self.override_display_name('ImageFlic', 'Flic', optional=optional_true)
        self.override_display_name('Rect2I', 'Area2I', optional=optional_true)
        self.override_display_name('Rect2F', 'Area2F', optional=optional_true)
        self.override_display_name('D3DRMVertex', 'Vertex3F', optional=optional_true)



#endregion


#######################################################################################

#region Setup global variables

db = LegoRRSymbolDatabase()
# Symbol.DB = db

db.populate_ghidra_primitives(preprocessor=True)


# GHIDRA_ALLOWED_TYPEDEFS = {'byte', 'uchar', 'ushort', 'uint', 'ulong', 'longlong', 'ulonglong', 'undefined', 'undefined1', 'undefined2', 'undefined4', 'undefined8', 'float10'}

ALLOWED_TYPEDEFS = {'Mesh_TextureStateChangeData', 'Mesh_Texture', 'Material', 'Animation_t', 'Movie_t', 'Material_t'}

EXCLUDE_FUNCTYPEDEFS = {'QsortCompare', 'PTOP_LEVEL_EXCEPTION_FILTER', '_PNH', 'WNDPROC', 'DLGPROC', 'MMIOPROC', 'FARPROC'}

#region OLD TYPEDEF'ING

# db.add(TypedefSymbol('FILE', 'void', hide=True))

# db.add(PrimitiveSymbol('point', 8))
# db.add(PrimitiveSymbol('vector3', 12))
# db.add(PrimitiveSymbol('rect', 16))


# # add_wintype(db, 'GUID', 'guid')
# # add_wintype(db, 'IID', 'GUID')
# # add_wintype(db, 'CLSID', 'GUID')

# db.add(TypedefSymbol('LPGUID', 'GUID', pointers=1, hide=True))

# db.add(TypedefSymbol('IID', 'GUID', hide=True))
# db.add(TypedefSymbol('CLSID', 'GUID', hide=True))

# db.add(TypedefSymbol('VOID', 'void', hide=True))
# db.add(TypedefSymbol('BOOL', 'int', hide=True))
# db.add(TypedefSymbol('BYTE', 'unsigned char', hide=True))
# db.add(TypedefSymbol('WORD', 'unsigned short', hide=True))
# db.add(TypedefSymbol('DWORD', 'unsigned long', hide=True))
# db.add(TypedefSymbol('CHAR', 'char', hide=True))
# db.add(TypedefSymbol('WCHAR', 'wchar_t', hide=True))
# db.add(TypedefSymbol('SHORT', 'short', hide=True))
# db.add(TypedefSymbol('INT', 'int', hide=True))
# db.add(TypedefSymbol('UINT', 'unsigned int', hide=True))
# db.add(TypedefSymbol('LONG', 'long', hide=True))
# db.add(TypedefSymbol('ULONG', 'unsigned long', hide=True))

# db.add(TypedefSymbol('HRESULT', 'long', hide=True))
# db.add(TypedefSymbol('MCIERROR', 'DWORD', hide=True))

# db.add(TypedefSymbol('IUnknown', 'void', hide=True))
# db.add(TypedefSymbol('IDirectDraw', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDraw2', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDraw3', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDraw4', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDrawSurface', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDrawSurface2', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDrawSurface3', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDrawSurface4', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDrawClipper', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectDrawPalette', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInput', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputA', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputW', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInput2A', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInput2W', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInput8A', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInput8W', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputDevice', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputDeviceA', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputDeviceW', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputDevice2A', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputDevice2W', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputDevice8A', 'IUnknown', hide=True))
# db.add(TypedefSymbol('IDirectInputDevice8W', 'IUnknown', hide=True))

# db.add(TypedefSymbol('LPGUID', 'GUID', pointers=1, hide=True))

# db.add(TypedefSymbol('LPSTR', 'CHAR', pointers=1, hide=True))
# db.add(TypedefSymbol('LPCSTR', 'CHAR', pointers=1, hide=True))
# db.add(TypedefSymbol('LPWSTR', 'WCHAR', pointers=1, hide=True))
# db.add(TypedefSymbol('LPCWSTR', 'WCHAR', pointers=1, hide=True))


# db.add(TypedefSymbol('LPVOID', 'VOID', pointers=1, hide=True))
# db.add(TypedefSymbol('LPBOOL', 'BOOL', pointers=1, hide=True))
# db.add(TypedefSymbol('LPBYTE', 'BYTE', pointers=1, hide=True))
# db.add(TypedefSymbol('LPWORD', 'WORD', pointers=1, hide=True))
# db.add(TypedefSymbol('LPDWORD', 'DWORD', pointers=1, hide=True))

# db.add(PrimitiveSymbol('GUID', 16))

# db.add(TypedefSymbol('HANDLE', 16))

#endregion


#endregion


#######################################################################################

#region ## MAIN FUNCTION ##

def main(argv:Optional[list]=None) -> int:

    #region ## PARSER SETUP ##
    import argparse
    parser = argparse.ArgumentParser(
        description='Transform Ghidra code exports into better formats',
        add_help=True)
    
    # parser.add_argument('input', metavar='INPUTEXE', help='original executable to patch (LegoRR.exe)')
    # oparser = parser.add_argument_group('output options')
    # ogroup = oparser.add_mutually_exclusive_group(required=False)
    # ogroup.add_argument('-o', '--output', metavar='OUTPUTEXE', default=None, help='write to new executable output file')
    # ogroup.add_argument('-n', '--name', metavar='OUTPUTNAME', dest='rename', default=None, help='write to new executable name in same directory')
    # ogroup.add_argument('-r', '--replace', action='store_true', default=False, help='overwrite original executable')
    # ogroup.add_argument('-b', '--backup', action='store_true', default=False, help=f'overwrite original executable and create *{BACKUP_CONST}.exe backup')
    # parser.add_argument('-q', '--quiet', action='store_true', default=False, help='don\'t print actions being performed')
    # parser.add_argument('-T', '--test', action='store_true', default=False, help='test patch without saving any changes')

    #endregion

    ###########################################################################

    #region ## PARSER VALIDATION ##

    args = parser.parse_args(argv)

    print('Main function not implemented yet...')

    #endregion

    ###########################################################################

    return 0

#endregion


###########################################################################

del Optional  # cleanup declaration-only imports


## MAIN CONDITION ##

if __name__ == '__main__':
    exit(main())
