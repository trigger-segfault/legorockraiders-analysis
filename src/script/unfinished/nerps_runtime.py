
import enum, io, operator, os
from collections import namedtuple
from enum import IntEnum, IntFlag
from struct import Struct, pack, unpack
from typing import Dict, Iterable, Iterator, List, Optional, Tuple, Type, Union
#from typing Literal

# from typing import *

class NERPsOpcode(IntFlag):
    Load     = 0x0000 # Load literal integer
    Operator = 0x0001 # Comparisons between instructions
    Function = 0x0002 # Call hardcoded NERPs functions
    Label    = 0x0004 # Define label at instruction index
    #                 # (serves no purpose during code execution)
    Jump     = 0x0008 # Unconditional jump to instruction index
    # Load opcode is used when none of these values mask against the opcode
    Mask     = (Operator|Function|Label|Jump),
    #
    @property
    def base(self) -> 'NERPsOpcode':
        if self & NERPsOpcode.Function:
            return NERPsOpcode.Function
        elif self & NERPsOpcode.Operator:
            return NERPsOpcode.Operator
        elif self & NERPsOpcode.Label:
            return NERPsOpcode.Label
        elif self & NERPsOpcode.Jump:
            return NERPsOpcode.Jump
        else:
            return NERPsOpcode.Load
    @property
    def mnemonic(self) -> str:
        MNS = {0x0: 'ldc.i', 0x1: 'op', 0x2: 'call', 0x4: 'label', 0x8: 'brtrue'}
        # OPS = {0:'andl', 1:'notl', 2:'orl', 3:'bslash', 4:'test', 5:'cgt', 6:'clt', 7:'ceq', 8:'cge', 9:'cle', 10:'cne'}
        mn = MNS[self.base]
        # if self is not base: # 
        # #
        # if base is NERPsOpcode.Load:
        #     m = 'ldc.i'
        if (self.value & ~self.base.value) == 0:
            # Normal opcode
            return mn
        else:
            # Abusive opcode that takes advantage of extra bits for function arguments
            return f'{mn}:{self.value:04x}'


class NERPsOperator(IntEnum):
    And    =  0 # "+"
    Not    =  1 # "#" ([unary], preserves cmp)
    Or     =  2 # "/"
    BSlash =  3 # "\" ([no effect], preserves cmp, resets Not)
    Test   =  4 # "?" ([no effect], preserves cmp, resets Not)
    Cgt    =  5 # ">"
    Clt    =  6 # "<"
    Ceq    =  7 # "="
    Cge    =  8 # ">="
    Cle    =  9 # "<="
    Cne    = 10 # "!="
    #
    @classmethod
    def from_operator(cls, op:str, error:bool=True) -> Optional['NERPsOperator']:
        OPS = ("+", "$", "/", "\\", "?", ">", "<", "=", ">=", "<=", "!=")
        try:
            return NERPsOperator(OPS.index(op))
        except ValueError:
            if error: raise
            return None
    #
    @property
    def operator(self) -> str:
        OPS = ("+", "$", "/", "\\", "?", ">", "<", "=", ">=", "<=", "!=")
        return OPS[self.value]
    #
    @property
    def is_unary(self) -> bool:
        return self in (NERPsOperator.Not,)
    @property
    def preserves_cmp(self) -> bool:
        return self in (NERPsOperator.Not, NERPsOperator.BSlash, NERPsOperator.Test)
    @property
    def is_comparison(self) -> bool:
        return self not in (NERPsOperator.BSlash, NERPsOperator.Test)
    #
    def compare(self, a:Union[int,bool], b:Optional[Union[int,bool]]=None) -> Union[int,bool]:
        if (b is None) != self.is_unary:
            if b is None: raise TypeError('b must be int for binary NERPsOperator')
            else:         raise TypeError('b must be None for unary NERPsOperator')
        CMPS = (operator.and_, operator.not_, operator.or_, int, int, operator.gt, operator.lt, operator.eq, operator.ge, operator.le, operator.ne)
        if not isinstance(a, (int,bool)):
            raise TypeError(f'a must be int or bool, not {a.__class__.__name__}')
        if self.is_unary:
            if b is not None:
                raise TypeError(f'b must be None for unary operator, not {b.__class__.__name__}')
            return CMPS[self.value](int(a & 0xffffffff))
        else:
            if b is None or not isinstance(b, (int,bool)):
                raise TypeError(f'b must be int or bool for binary operator, not {b.__class__.__name__}')
            return CMPS[self.value](int(a & 0xffffffff), int(b & 0xffffffff))


class NERPsArgs(IntEnum):
    Return0 = 0 # Only type allowed as function argument
    Return1 = 1
    Return2 = 2
    Void0   = 3
    Void1   = 4
    Void2   = 5
    Void3   = 6
    End     = 7 # "**End Of List**" (not a valid type)
    #
    @classmethod
    def from_signature(cls, is_return:bool, num_args:int, error:bool=True) -> Optional['NERPsArgs']:
        ARGS = ((True,0), (True,1), (True,2), (False,0), (False,1), (False,2), (False,3), (None,-1))
        try:
            return NERPsArgs(ARGS.index( (is_return,num_args) ))
        except ValueError:
            if error: raise
            return None
    #
    @property
    def signature(self) -> Tuple[bool,int]:
        return (self.is_return, self.num_args)
    @property
    def is_return(self) -> bool:
        RETS = (True, True, True, False, False, False, False, None)
        return RETS[self.value]
        #return self in (NERPsArgs.Return0, NERPsArgs.Return1, NERPsArgs.Return2)
    @property
    def is_void(self) -> bool:
        RETS = (False, False, False, True, True, True, True, None)
        return RETS[self.value]
        #return self in (NERPsArgs.Void0, NERPsArgs.Void1, NERPsArgs.Void2, NERPsArgs.Void3)
    @property
    def num_args(self) -> int:
        NARGS = (0, 1, 2, 0, 1, 2, 3, -1)
        return NARGS[self.value]


# NERPsFunc = namedtuple('NERPsFunc', ('id', 'name', 'func', 'argc'))

class NERPsTraits(namedtuple('_NERPsTraits', ('constant', 'unimplemented', 'dup_name', 'register'))):
    constant:Optional[int]
    unimplemented:bool
    dup_name:Optional[str]
    register:Optional[Tuple[str,str,int]]
    #register:Optional[Tuple[Literal["Get","Set","Add","Sub"],Literal["R","Timer"],int]]
    # reg_type:Optional[Literal["R","Timer"]]
    # reg_num:Optional[int]
    # reg_action:Optional[Literal["Get","Set","Add","Sub"]]
    #
    #def __new__(cls, constant:Optional[int]=None, unimplemented:Optional[bool]=None, dup_name:Optional[str]=None, register:Optional[Tuple[Literal["Get","Set","Add","Sub"],Literal["R","Timer"],int]]=None):
    def __new__(cls, constant:Optional[int]=None, unimplemented:Optional[bool]=None, dup_name:Optional[str]=None, register:Optional[Tuple[str,str,int]]=None):
        unimplemented = False if unimplemented is None else bool(unimplemented)
        return super().__new__(cls, constant, unimplemented, dup_name, register)

class NERPsFunction(namedtuple('_NERPsFunction', ('id', 'name', 'args', 'func', 'traits'))):
    id:int
    name:str
    args:NERPsArgs
    func:Optional[str]
    traits:NERPsTraits
    #
    def __new__(cls, id:int, name:str, args:NERPsArgs, func:Optional[str]=None, traits:Optional[NERPsTraits]=None):
        if traits is None: traits = NERPsTraits()
        return super().__new__(cls, int(id), name, NERPsArgs(args), func, traits)

NERPsFunc = NERPsFunction


class NERPsLabel(namedtuple('_NERPsLabel', ('address', 'number'))):
    address:int
    number:int
    #
    def __new__(cls, address:int, number:int):
        return super().__new__(cls, int(address), int(number & 0xffff))


class NERPsInstruction(namedtuple('_NERPsInstruction', ('operand', 'opcode'))):
    _struct = Struct('<HH')
    #
    operand:int
    opcode:NERPsOpcode
    #
    @classmethod
    def calcsize(cls) -> int:
        return cls._struct.size
    @classmethod
    def iter_unpack(cls, buffer:bytes) -> Iterator['NERPsInstruction']:
        return (cls(*t) for t in cls._struct.iter_unpack(buffer))
    @classmethod
    def unpack(cls, buffer:bytes) -> 'NERPsInstruction':
        return cls(*cls._struct.unpack(buffer))
    @classmethod
    def unpack_from(cls, buffer:bytes, offset:Optional[int]=0) -> 'NERPsInstruction':
        return cls(*cls._struct.unpack_from(buffer, offset))
    def pack(self) -> bytes:
        return self._struct.pack(*self)
    def pack_into(self, buffer:bytearray, offset:int) -> None:
        self._struct.pack_into(buffer, offset, *self)
    #
    def __new__(cls, operand:Union[int,NERPsOperator], opcode:Union[int,NERPsOpcode]):
        return super().__new__(cls, int(operand & 0xffff), NERPsOpcode(opcode))
    #
    @property
    def uint16(self) -> int:
        """Operand as an unsigned 16-bit integer."""
        return self.operand & 0xffff
    @property
    def sint16(self) -> int:
        """Operand as a signed 16-bit integer."""
        return unpack('<h', pack('<H', self.uint16))[0]
    @property
    def uint32(self) -> int:
        """Operand as an unsigned 32-bit integer by treating the opcode as the hiword."""
        return self.uint16 | ((self.opcode & 0xffff) << 16)
    @property
    def sint32(self) -> int:
        """Operand as a signed 32-bit integer by treating the opcode as the hiword."""
        return unpack('<i', pack('<I', self.uint32))[0]
    #
    def display(self, script:'NERPsScript') -> str:
        mn = self.opcode.mnemonic
        opbase = self.opcode.base
        operand = self.uint16
        value = f'{operand:d}'
        hexvalue = f'0x{operand:04x}'
        comment = None
        if opbase is NERPsOpcode.Function:
            funcId = operand
            #value = f'0x{funcId:04x}'
            if funcId < len(NERPS_FUNCS):
                func = NERPS_FUNCS[funcId]
                ret = '???'
                if func.args.is_return: ret = 'int' #'ret' #'int'
                elif func.args.is_void: ret = 'void'
                else:                   ret = '???'
                if func.args.num_args != -1:
                    args = ', '.join(f'p{i+1}' for i in range(func.args.num_args))
                else:
                    args = '???'
                # comment = f'{ret} {func.name}({args})'
                comment = f'{ret}({args})'
                value = func.name
            #
        elif opbase is NERPsOpcode.Operator:
            opId = operand
            OPS = {0:'andl', 1:'notl', 2:'orl', 3:'cont', 4:'test', 5:'cgt', 6:'clt', 7:'ceq', 8:'cge', 9:'cle', 10:'cne'}
            op = OPS.get(opId)
            if op is not None:
                comment = f'\'{NERPsOperator(opId).operator}\''
                value = op
        elif opbase is NERPsOpcode.Label:
            value = f'label_{operand:d}'
        elif opbase is NERPsOpcode.Jump:
            label = None
            if script is not None:
                for label in script.labels:
                    if operand == label.address:
                        comment = f'label_{label.number:d}'
                        break
        else:
            if opbase != self.opcode:
                comment = f'0x{self.uint32:08x}'
            else:
                comment = f'0x{(self.sint16 & 0xffffffff):08x}'
        if comment is not None:
            comment = f' ; {comment}'
        else:
            comment = ''
        return f'{self.opcode.mnemonic.ljust(11)} {str(value).ljust(11)}{comment}'


class NERPsScript:
    __slots__ = ('instructions', 'labels', 'eip', 'eax', 'ebx', 'neg', 'cmp')
    _FUNCID_STOP:int = 0
    _FUNCTIONS:Tuple[NERPsFunc]
    #
    instructions:Tuple[NERPsInstruction,...]
    labels:Tuple[NERPsLabel]
    eip:int  # Instruction pointer (index)
    eax:int  # Left argument of binary comparison. Result of instruction. Condition for action.
    ebx:int  # Right argument of binary comparison. Argument for unary comparison.
    neg:bool # Not comparison on ebx before binary comparison
    cmp:Optional[NERPsOperator] # Binary comparison between eax,ebx
    #
    def __init__(self, instructions:Optional[Iterable[NERPsInstruction]]=None, labels:Optional[Iterable[int]]=None, eip:Optional[int]=None, eax:Optional[int]=None, ebx:Optional[int]=None, neg:Optional[bool]=None, cmp:Optional[NERPsOperator]=None):
        self.instructions = () if instructions is None else tuple(instructions)
        self.labels = () if labels is None else tuple(labels)
        self.eip = 0 if eip is None else int(eip)
        self.eax = 0 if eax is None else int(eax)
        self.ebx = 0 if ebx is None else int(ebx)
        self.neg = False if neg is None else bool(neg)
        self.cmp = None  if cmp is None else NERPsOperator(cmp)
    #
    def __repr__(self) -> str:
        return f'{self.__class__.__name__}(eip={self.eip}, eax={self.eax:#x}, ebx={self.ebx:#x}, neg={self.neg}, cmp={self.cmp})'
    def __str__(self) -> str:
        return f'<{self.__class__.__name__}: [{len(self.instructions)} instrs, {len(self.labels)} labels] eip={self.eip} eax={self.eax:#x} ebx={self.ebx:#x} neg={self.neg} cmp={self.cmp}>'
    #
    def __len__(self) -> int:
        return len(self.instructions)
    def __iter__(self) -> Iterator['NERPsInstruction']:
        return iter(self.instructions)
    def __getitem__(self, key):
        return self.instructions[key]
    def __contains__(self, instr:NERPsInstruction) -> bool:
        return instr in self.instructions
    #
    @classmethod
    def load(cls, file:Union[str,bytes,bytearray,io.BufferedReader]) -> 'NERPsScript':
        if isinstance(file, str):
            with open(file, 'rb') as f:
                data = f.read()
        elif hasattr(file, 'read'):
            data = file.read()
        else:
            data = file # assume bytes/bytearray
        if len(data) & 0x3:
            # Length is not a multiple of 4, last 1-3 bytes serve no purpose.
            data = data[:len(data) & ~0x3] # Round down to unit of 4 (bitwise)
        #
        instructions = tuple(NERPsInstruction.iter_unpack(data))
        labels = []
        for i,instr in enumerate(instructions):
            # TODO: Should we compare with masking like elsewhere? Probably not.
            if instr.opcode is NERPsOpcode.Label:
                labels.append( NERPsLabel(i, instr.uint16) )
        #
        return cls(instructions=instructions, labels=labels)
    #
    #
    @property
    def current(self) -> NERPsInstruction:
        """Returns the instruction at the current eip (instruction pointer)."""
        return self.instructions[self.eip]
    @property
    def end_of_script(self) -> bool:
        """Returns True if the eip (instruction pointer) is at the end of the script (instruction list)."""
        return self.eip >= len(self.instructions)
    #
    def reset(self) -> None:
        """Clears the interpreter state, for use before script execution.
        """
        self.eip = 0
        self.eax = 0
        self.ebx = 0
        self.neg = False
        self.cmp = None
    #
    def clone(self) -> 'NERPsScript':
        """Returns a copy of the current interpreter state.
        """
        return self.__class__(instructions=self.instructions, labels=self.labels, eip=self.eip, eax=self.eax, ebx=self.ebx, neg=self.neg, cmp=self.cmp)
    #
    def eval_arg(self, instr:NERPsInstruction) -> int:
        """Evaluates an instruction used as a function argument.
        """
        # Unlike elsewhere, Function is not checked as a mask here.
        if instr.opcode == NERPsOpcode.Function and self._FUNCTIONS[instr.uint16].args == NERPsArgs.Return0:
            return self.eval_function(instr.uint16, [])
        else:
            return instr.uint32
    #
    def eval_stack(self, num_args:int) -> List[int]:
        """Evaluates all instructions used as arguments for a function.
        """
        return [self.eval_arg(self.instructions[self.eip + 1 + i]) for i in range(num_args)]
    #
    def eval_function(self, funcId:int, stack:List[int]) -> Optional[int]:
        """Executes a NERPs function by ID and returns an integer value (or None for void returns).
        """
        func = self._FUNCTIONS[funcId]
        if func.traits.constant is not None:
            return int(func.traits.constant)
        #
        return None # <NOT IMPLEMENTED>
    #
    #
    def _do_function(self, *args, **kwargs) -> None:
        """(Expression) Execute a Function instruction (when has a return, and not a function argument).
        (Action) Execute a Function instruction (when void return, and if eax is true).
        """
        # NOTE: Stop function should be handled be the caller
        funcId = self.current.uint16
        if funcId == self._FUNCID_STOP and (self.eax or self.cmp is None):
            return  # Stop function (funcId:0)
        #
        # Functions have some very awkward behavior here.
        #
        # A) Function arguments cannot be complex. They must either be an integer literals,
        #    or a 0-argument functions that returns a value (i.e. True, False).
        #    If a function argument is something else, the raw uint32 value of the instruction is used.
        #    `SetR2 SetR2` would result in `SetR2 0x2001b`
        #     (where `0x20000` is the opcode for functions, and 0x1b is the function ID for `SetR2`)
        #
        # B) Functions that returns a value are ONLY designed to work on as part of an expression.
        #    Basically, they cannot be used as the action after '?', as they do not check the
        #     condition register, and will always execute.
        #    Likewise, functions with a void return always check the conditional register, which means
        #     they can technically be changed after any return-function or literal.
        #
        # C) Based on the above information, and how the Operator opcode works, the Test operator '?'
        #     seems to be COMPLETELY USELESS!!
        #    `TRUE ? Stop` would supposedly be identical to just `TRUE Stop`.
        #    Try it for yourself by uncommenting the code at the beginning of this instruction loop.
        #
        func = self._FUNCTIONS[funcId]
        argc = func.args.num_args
        #
        if func.args.is_return:
            stack = self._eval_stack(argc)
            self.ebx = self.eval_function(funcId, stack)
            #
            # Increment eip for arguments.
            self.eip += argc
            self._end_expression()
            #
        elif func.args.is_void:
            # Execute function if last expression is true.
            if self.eax:
                stack = self._eval_stack(argc)
                self.eval_function(funcId, stack)
            #
            # Always increment eip for arguments, regardless of executing the function.
            self.eip += argc
            self._end_action()
            #
        else:
            # preserves eax, neg, cmp
            pass
    #
    def _do_operator(self, *args, **kwargs) -> None:
        """(Operator) Execute an Operator instruction (change comparisons performed on Expression types).
        """
        op = NERPsOperator(self.current.uint16)
        if op is NERPsOperator.Not: # #
            self.neg = True
            # preserves cmp
        elif op.is_comparison:      # +, /, >, <, =, >=, <=, !=
            self.cmp = op
            self.neg = False
        else:                       # \, ?
            self.neg = False
            # preserves cmp
        # preserves eax
    #
    def _do_label(self, *args, **kwargs) -> None:
        """(Action) Marks a label, but does nothing.
        """
        self._end_action()
    #
    def _do_jump(self, *args, **kwargs) -> None:
        """(Action) Execute a Jump instruction (if eax is true).
        """
        # Jump if last expression is true.
        if self.eax:
            # Note that EIP is still incremented after this, so labels serve a semi-important role
            self.eip = self.current.uint16
        #
        self._end_action()
    #
    def _do_load(self, *args, **kwargs) -> None:
        """(Expression) Execute a Load instruction (when not a function argument).
        """
        # Sign-extend 16-bit integer to 32-bit integer.
        # Note however, that values are ALWAYS compared as unsigned.
        self.ebx = int(self.current.sint16 & 0xffffffff)
        self._end_expression()
    #
    #
    def _end_expression(self) -> None:
        """End of an instruction type expected on the left side of an "?" statement.
        """
        a, b = int(self.eax & 0xffffffff), int(self.ebx & 0xffffffff)
        #
        if self.neg:
            b = int(not b)
        #
        ret = b
        cmp = self.cmp
        if cmp is not None:
            ret = cmp.compare(a, b)
            # if   cmp is NERPsOperator.And: ret = (a and b) # "+"
            # elif cmp is NERPsOperator.Or:  ret = (a or  b) # "/"
            # elif cmp is NERPsOperator.Cgt: ret = (a >  b)  # ">"
            # elif cmp is NERPsOperator.Clt: ret = (a <  b)  # "<"
            # elif cmp is NERPsOperator.Ceq: ret = (a == b)  # "="
            # elif cmp is NERPsOperator.Cge: ret = (a >= b)  # ">="
            # elif cmp is NERPsOperator.Cle: ret = (a <= b)  # "<="
            # elif cmp is NERPsOperator.Cne: ret = (a != b)  # "!="
        #
        self.eax = int(ret)
        self.neg = False
        self.cmp = NERPsOperator.And
    #
    def _end_action(self) -> None:
        """End of an instruction type expected on the right side of an "?" statement.
        """
        self.eax = 0
        self.neg = False
        self.cmp = None
    #
    #
    def step(self, *args, **kwargs) -> bool:
        """Run a single instruction.
        """
        if self.eip >= len(self.instructions):
            return True # End of script
        #
        # NERPs treats instructions as a single DWORD (loword=operand, hiword=opcode), and operates on them as such.
        # This is probably the reason why we have pointless bitwise AND comparisons
        # for opcode types instead of equality comparisons...
        opcode = self.current.opcode
        #
        if opcode & NERPsOpcode.Function:
            funcId = self.current.uint16
            if funcId == self._FUNCID_STOP and (self.eax or self.cmp is None):
                return True # Stop function (funcId:0)
            #
            self._do_function(*args, **kwargs)
        elif opcode & NERPsOpcode.Operator:
            self._do_operator(*args, **kwargs)
        elif opcode & NERPsOpcode.Label:
            self._do_label(*args, **kwargs) # does nothing asside from resetting states
        elif opcode & NERPsOpcode.Jump:
            self._do_jump(*args, **kwargs)
        else: #elif not (opcode & NERPsOpcode.Mask): # NERPsOpcode.Load
            self._do_load(*args, **kwargs)
        #
        self.eip += 1
        return False




# class Color(enum.IntEnum):
#     Black = 30
#     DRed  = 31
#     DGreen = 32
#     DYellow = 33
#     DBlue = 34
#     DMagenta = 35
#     DCyan = 36
#     Gray = 37
#     DGray = 90
#     BRed = 91
#     BGreen = 92
#     BYellow = 93
#     BBlue = 94
#     BMagenta = 95
#     BCyan = 96
#     White = 97

class Color(enum.IntEnum):
    Default  = 0
    Reset    = 0
    #
    Black    = 30
    DRed     = 31
    DGreen   = 32
    DYellow  = 33
    DBlue    = 34
    DMagenta = 35
    DCyan    = 36
    Gray     = 37
    DGray    = 90
    Red      = 91
    Green    = 92
    Yellow   = 93
    Blue     = 94
    Magenta  = 95
    Cyan     = 96
    White    = 97
    #
    def __bool__(self) -> bool:
        return True
    #
    @property
    def ansi(self) -> str:
        return f'\x1b[{self.value:d}m'

class ColorScheme:
    __slots__ = ('default', 'number', 'constant', 'function', 'getter', 'setter', 'reg_function', 'reg_getter', 'reg_setter', 'timer_function', 'timer_getter', 'timer_setter', 'stop', 'operator', 'label', 'goto', 'comment')
    default:Color
    number:Color
    constant:Color
    function:Color
    getter:Color
    setter:Color
    reg_function:Color
    reg_getter:Color
    reg_setter:Color
    timer_function:Color
    timer_getter:Color
    timer_setter:Color
    stop:Color
    operator:Color
    label:Color
    goto:Color
    comment:Color
    #
    def __init__(self, default:Color=Color.Default, number:Color=None, constant:Color=None, function:Color=None, getter:Color=None, setter:Color=None, reg_function:Color=None, reg_getter:Color=None, reg_setter:Color=None, timer_function:Color=None, timer_getter:Color=None, timer_setter:Color=None, stop:Color=None, operator:Color=None, label:Color=None, goto:Color=None, comment:Color=None):
        if default is None: default = Color.Default
        self.default  = default
        self.number   = number or default
        self.constant = constant or getter or function or default
        self.function = function or default
        self.getter   = getter or function or default
        self.setter   = setter or function or default
        self.reg_function = reg_function or function or default
        self.reg_getter   = reg_getter or reg_function or getter or function or default
        self.reg_setter   = reg_setter or reg_function or setter or function or default
        self.timer_function = timer_function or function or default
        self.timer_getter   = timer_getter or timer_function or getter or function or default
        self.timer_setter   = timer_setter or timer_function or setter or function or default
        self.stop     = stop or setter or function or default
        self.operator = operator or default
        self.label    = label or default
        self.goto     = goto or label or default
        self.comment  = comment or default

colors1 = ColorScheme(constant=Color.Blue, number=Color.Green, getter=Color.Cyan, setter=Color.Yellow, stop=Color.Red, operator=Color.Gray, label=Color.DGray, goto=Color.Magenta, comment=Color.DGreen)

colors2 = ColorScheme(constant=Color.Blue, number=Color.Red, function=Color.Magenta, reg_function=Color.Yellow, timer_function=Color.Cyan, stop=Color.Blue, operator=Color.Gray, label=Color.DGreen, goto=Color.DGreen, comment=Color.DGray)

import string
def decompile2(instructions:List[NERPsInstruction], labels:List[NERPsLabel], letterset:str=None, colors:ColorScheme=None) -> str:
    if letterset is None: letterset = string.ascii_uppercase
    if colors is None: colors = ColorScheme()
    labelmap = {}
    for label in labels:
        labelmap.setdefault(label.address, []).append(label)
    #
    def get_labelname(label:NERPsLabel):
        if len(labelmap[label.address]) == 1:
            if label.address == 0 :                    return 'Begin'
            elif label.address+1 == len(instructions): return 'End'
        #
        index = label.number
        s = [ letterset[index % len(letterset)] ]
        index //= len(letterset)
        while index != 0:
            s.insert(0, letterset[index % len(letterset)])
            index //= len(letterset)
        return f'Label_{"".join(s)}'
    #
    def get_func(instr:NERPsInstruction, default=None) -> NERPsFunction:
        if instr.opcode & NERPsOpcode.Function:
            funcId = instr.uint16
            if funcId + 1 < len(NERPS_FUNCS):
                return NERPS_FUNCS[funcId]
        return default
    #
    def get_symbol(i:int, is_arg:bool=False):
        instr:NERPsInstruction = instructions[i]
        opcode = instr.opcode
        col = colors.default # default (grey)
        if opcode & NERPsOpcode.Function:
            func = get_func(instr)
            traits = func.traits
            register = traits.register
            col = Color.Yellow # bright yellow
            col = colors.function
            if func is not None:
                sym = func.name
                if instr.uint16 == 0: # Stop
                    #col = Color.Magenta # bright magenta
                    col = Color.Red # bright red
                    col = colors.stop
                elif traits.constant is not None and not traits.unimplemented:
                    col = Color.Blue # bright blue
                    col = colors.constant
                    sym = sym.upper()
                elif func.args.is_void:
                    #col = Color.DYellow # dark yellow
                    col = Color.Yellow # bright yellow
                    #col = Color.Red # bright red
                    col = colors.setter
                    if register and register[1] == 'R':
                        col = colors.reg_setter
                    if register and register[1] == 'Timer':
                        col = colors.timer_setter
                elif func.args.is_return:
                    col = Color.Cyan # bright cyan
                    col = colors.getter
                    if register and register[1] == 'R':
                        col = colors.reg_getter
                    if register and register[1] == 'Timer':
                        col = colors.timer_getter
            else:
                sym = f'FUNC_{instr.uint16:d}'
        elif opcode & NERPsOpcode.Operator:
            try:    sym = NERPsOperator(instr.uint16).operator
            except: sym = f'OP_{instr.uint16:d}'
            col = Color.Gray # grey
            col = colors.operator
        elif opcode & NERPsOpcode.Label:
            sym = f'{get_labelname(NERPsLabel(i, instr.uint16))}:'
            col = Color.DGray # dark grey ##97 # bright white
            col = colors.label
        elif opcode & NERPsOpcode.Jump:
            labellist = labelmap.get(instr.uint16)
            if labellist: sym = f':{get_labelname(labellist[0])}'
            else:         sym = f':JUMP_{instr.uint16:d}'
            #col = Color.DMagenta # dark magenta
            col = Color.Magenta # bright magenta
            col = colors.goto
        else:
            sym = f'{instr.uint16:d}'
            col = Color.Green # bright green
            col = colors.number
        return f'{col.ansi}{sym}{Color.Reset.ansi}'
    #
    lines, line, linePrefix = [], [], []
    #
    def end_line():
        if line: lines.append(''.join(linePrefix) + ' '.join(line))
        line.clear()
        linePrefix.clear()
    def indent():
        if not line:
            linePrefix.append('\t')
    #
    cmp = False
    i = 0
    while i < len(instructions):
        instr = instructions[i]
        if instr.opcode.base is NERPsOpcode.Operator:
            line.append(get_symbol(i))
        elif instr.opcode.base is NERPsOpcode.Function:
            func = get_func(instr)
            # Stop (funcId:0) can be a standalone statement without `TRUE ?`
            if (func.args.is_return or instr.uint16 == 0) and not cmp:
                end_line()
            indent()
            line.append(get_symbol(i))
            for j in range(func.args.num_args):
                line.append(get_symbol(i + 1 + j, is_arg=True))
            i += func.args.num_args
        elif instr.opcode.base is NERPsOpcode.Label:
            if not cmp:
                end_line()
            line.append(get_symbol(i))
        elif instr.opcode.base is NERPsOpcode.Jump:
            indent()
            line.append(get_symbol(i))
        else: # NERPsOpcode.Load
            if not cmp:
                end_line()
            indent()
            line.append(get_symbol(i))
        cmp = (instr.opcode.base is NERPsOpcode.Operator)
        i += 1
    end_line()
    return '\n'.join(lines)


# ns = NERPsScript.load(r"C:\<FILLMEIN>\Data\Levels\GameLevels\Level01\01.npl")

# for instr in ns.instructions: print('  ' + instr.display(ns))


# print(decompile2(ns.instructions, ns.labels))

def showlevel2(name, letterset:str=None, colors:ColorScheme=None):
    if isinstance(name,int) or (name.startswith('Level') and name[5].isdigit()) or (name.startswith('L') and name[1].isdigit()):
        group = 'GameLevels'
        if isinstance(name,int):
            name = f'Level{name:02d}'
        elif name.startswith('L'):
            num = int(name[1:])
            name = f'Level{num:02d}'
    else:
        group = 'TutorialLevels'
        TUTOS = {'DE':'Defence', 'D':'Dig', 'B':'Build', 'M':'Move', 'G':'Geo'}
        if name[:2] in TUTOS and name[2].isdigit():
            pre = name[:2]
            num = int(name[2:])
            name = f'{TUTOS[pre]}Tuto_{num:02d}'
        elif name[:1] in TUTOS and name[1].isdigit():
            pre = name[:1]
            num = int(name[1:])
            name = f'{TUTOS[pre]}Tuto_{num:02d}'
        # else:
        # tuto
        # if name.startswith('DE'):
        #     pre = 'DE'
        #     tuto = 'Defence'
        #     num = int(name[2:])
        #     name = f'{name[:2]}{int(name[2:]):02d}'
    leveldir = f'Levels/{group}/{name}'
    DATADIR = r"C:/<FILLMEIN>/Data"
    path = f'{DATADIR}/{leveldir}'
    import os
    found = []
    for f in os.listdir(path):
        if os.path.splitext(f)[1].lower() == '.npl':
            found.append(f)
    if len(found) == 0:
        print(f'No .npl files found [{leveldir}]')
    elif len(found) > 1:
        print(f'More than one .npl file found [{leveldir}]:')
        print(*['\t'+f for f in found], sep='\n')
    else:
        npl = NERPsScript.load(f'{path}/{found[0]}')
        print(decompile2(npl.instructions, npl.labels, letterset=letterset, colors=colors))

def findnerps(basedir:str, found:List=[]) -> List[str]:
    #found = []
    for f in os.listdir(basedir):
        fpath = os.path.join(basedir, f)
        if os.path.isdir(fpath):
            findnerps(fpath, found)
        elif os.path.splitext(f)[1].lower() == '.npl':
            found.append(fpath)
    return found


LEVELDIR = r"C:/<FILLMEIN>/Data/Levels"
npls = findnerps(LEVELDIR)
nplss = [NERPsScript.load(npl) for npl in npls]

class hexint(int):
    def __repr__(self) -> str: return hex(self)
    __str__ = __repr__

#def findsetmsg(npls:List[str], basedir=LEVELDIR):
def findsetmsg(basedir:str):
    funcId = None
    for func in NERPS_FUNCS:
        if func.name.lower() == 'SetMessage'.lower():
            funcId = func.id
            break
    #
    npls = findnerps(LEVELDIR)
    args = {}
    for nplf in npls:
        nplf = nplf.replace('\\', '/')
        if nplf.lower().startswith(LEVELDIR.lower()):
            nplfdisp = nplf[len(LEVELDIR):]
            if nplfdisp[0] == '/':
                nplfdisp = nplfdisp[1:]
        #
        #found = []
        npl = NERPsScript.load(nplf)
        for i,instr in enumerate(npl.instructions):
            if instr.opcode.base is NERPsOpcode.Function and instr.uint16 == funcId:
                instrArg = npl.instructions[i + 2]
                if instrArg.opcode.base is NERPsOpcode.Function:
                    #argId = (NERPsOpcode.Function, NERPS_FUNCS[instrArg.uint16].name)
                    argId = NERPS_FUNCS[instrArg.uint16].name
                elif instrArg.opcode.base is NERPsOpcode.Load:
                    #argId = (NERPsOpcode.Load, hex(instrArg.uint16))
                    argId = hexint(instrArg.uint16)
                else:
                    raise ValueError(f'Invalid argument instruction: {instrArg}')
                args[argId] = args.setdefault(argId, 0) + 1
    return args

def findfunc(id:Union[int,str], default=...) -> NERPsFunction:
    if isinstance(id, str):
        name = id.lower()
        for func in NERPS_FUNCS:
            if func.name.lower() == name:
                return func
        if default is Ellipsis:
            raise KeyError(f'Function name not found: {id!r}')
    elif isinstance(id, int) and id >= 0x10000: # virtual address (func index numbers are uint16's)
        for func in NERPS_FUNCS:
            if int(func.func[4:], 16) == id:
                return func
        if default is Ellipsis:
            raise KeyError(f'Function address not found: 0x{id:08x}')
    elif isinstance(id, int): # table index
        if 0 <= id < (len(NERPS_FUNCS) - 1):
            return NERPS_FUNCS[id]
        if default is Ellipsis:
            raise ValueError(f'Index out of bounds: {id}')
    else:
        raise TypeError(f'Expected int or str, not {id.__class__.__name__}')
    return default

class FuncAnalysis:
    __slots__ = ('func', 'total_calls', 'script_calls', 'full_args', 'indiv_args')
    func:NERPsFunction
    total_calls:int
    script_calls:Dict[str,int]
    full_args:Dict[Tuple[Union[str,int],...],int]
    indiv_args:Tuple[Dict[Union[str,int],int],...]
    #
    DEFAULT_LOOKUP:Dict[int,'FuncAnalysis'] = {}
    # def __new__(cls, func:NERPsFunction, *args, **kwargs):
    #
    def __init__(self, func:NERPsFunction, total_calls:Optional[int]=None, script_calls:Optional[Dict[str,int]]=None, full_args:Optional[Dict[Tuple[Union[str,int],...],int]]=None, indiv_args:Optional[Tuple[Dict[Union[str,int],int],...]]=None):
        self.func = func if isinstance(func, NERPsFunction) else findfunc(func)
        #print(f'FuncAnalysis.__init__(func={self.func.name!r},...)')
        self.total_calls = 0 if total_calls is None else total_calls
        self.script_calls = {} if script_calls is None else script_calls
        self.full_args = {} if full_args is None else full_args
        self.indiv_args = tuple({} for _ in range(self.func.args.num_args)) if indiv_args is None else indiv_args
    #
    def __repr__(self) -> str:
        return f'{self.__class__.__name__}(id={self.id:d}, func={self.func.name!r}, calls={self.total_calls:d}, scripts=[{len(self.script_calls):d}], full_args=[{len(self.full_args):d}], indiv_args={tuple("["+str(len(a))+"]" for a in self.indiv_args)}])'
    __str__ = __repr__
    #
    @property
    def address(self) -> hexint: return hexint(self.func.func[4:], 16)
    @property
    def name(self) -> str: return self.func.name
    @property
    def id(self) -> int: return self.func.id
    @property
    def constant(self) -> Optional[int]: return self.func.traits.constant
    @property
    def is_constant(self) -> bool: return self.func.traits.constant is not None
    @property
    def dup_name(self) -> Optional[str]: return self.func.traits.dup_name
    @property
    def is_duplicate(self) -> bool: return self.func.traits.dup_name is not None
    @property
    def is_unimplemented(self) -> bool: return self.func.traits.unimplemented
    #
    @property
    def return_str(self) -> str:
        if self.func.args.is_return: return 'return'
        elif self.func.args.is_void: return 'void'
        else:                        return ''
    #
    @property
    def args_str(self) -> str:
        if self.func.args.num_args:
            return ', '.join(f'arg{i+1}' for i in range(self.func.args.num_args))
        else:
            return ''
    @property
    def signature_str(self) -> str:
        return f'{self.return_str} {self.name}({self.args_str})'
    #
    @property
    def args(self) -> NERPsArgs: return self.func.args
    @property
    def num_args(self) -> int: return self.func.args.num_args
    @property
    def has_args(self) -> bool: return self.func.args.num_args != 0
    @property
    def is_void(self) -> bool: return self.func.args.is_void
    @property
    def is_return(self) -> bool: return self.func.args.is_return
    @property
    def is_end(self) -> bool: return self.func.args is NERPsArgs.End
    #
    @property
    def is_arg(self) -> bool: return self.func.args is NERPsArgs.Return0



def get_analysis(func:Union[FuncAnalysis,NERPsFunction,int,str], lookup:Dict[int,FuncAnalysis]=FuncAnalysis.DEFAULT_LOOKUP) -> FuncAnalysis:
    if isinstance(func, FuncAnalysis):
        return func
    if not isinstance(func, NERPsFunction):
        func = findfunc(func)
    funcId = func.id
    analysis = lookup.get(funcId)
    if analysis is None:
        lookup[funcId] = analysis = FuncAnalysis(func)
    return analysis

def analyze_script(name:str, npl:NERPsScript, lookup:Dict[int,FuncAnalysis]=FuncAnalysis.DEFAULT_LOOKUP):
    i = 0
    instructions = npl.instructions
    while i < len(instructions):
        instr = instructions[i]
        if instr.opcode.base is NERPsOpcode.Function:
            analysis = get_analysis(instr.uint16, lookup)
            num_args = analysis.num_args
            analysis.total_calls += 1
            analysis.script_calls[name] = analysis.script_calls.setdefault(name, 0) + 1
            args = [None]*num_args
            for j in range(num_args):
                instrArg = instructions[i + 1 + j]
                if instrArg.opcode.base is NERPsOpcode.Function:
                    funcArg = NERPS_FUNCS[instrArg.uint16]
                    if funcArg.args is not NERPsArgs.Return0:
                        raise ValueError(f'Invalid argument instruction function: {instrArg}')
                    indivId = funcArg.name
                elif instrArg.opcode.base is NERPsOpcode.Load:
                    indivId = instrArg.uint16
                else:
                    raise ValueError(f'Invalid argument instruction opcode: {instrArg}')
                args[j] = indivId
                analysis.indiv_args[j][indivId] = analysis.indiv_args[j].setdefault(indivId, 0) + 1
            if num_args:
                fullId = tuple(args)
                analysis.full_args[fullId] = analysis.full_args.setdefault(fullId, 0) + 1
            i += num_args
        i += 1

def scan_scripts(basedir:str, lookup:Dict[int,FuncAnalysis]=FuncAnalysis.DEFAULT_LOOKUP, clear:bool=True):
    if clear: lookup.clear()
    #
    npls = findnerps(basedir)
    basedir_fmt = basedir.replace('\\', '/').lower()
    #
    for fpath in npls:
        fpath = fpath.replace('\\', '/')
        if fpath.lower().startswith(basedir_fmt):
            name = fpath[len(basedir_fmt):].lstrip('/')
            if name[0] == '/':
                name = name[1:]
        #
        npl = NERPsScript.load(fpath)
        analyze_script(name, npl, lookup)



scan_scripts(LEVELDIR)
get_analysis('SetMessage').indiv_args[1]

def scanfuncargs(basedir:str):
    # funcId = None
    # for func in NERPS_FUNCS:
    #     if func.name.lower() == 'SetMessage'.lower():
    #         funcId = func.id
    #         break
    #
    npls = findnerps(LEVELDIR)
    #ops = {} # type: Dict[NERPSOperator,int]
    calls = {}
    argsFull = {} # type: Dict[str, Dict[Tuple[Union[str,int],...],int]]
    argsIndiv = {} # type: Dict[str, Tuple[Dict[Union[str,int],int],...]]
    args = {}
    for nplf in npls:
        nplf = nplf.replace('\\', '/')
        if nplf.lower().startswith(LEVELDIR.lower()):
            nplfdisp = nplf[len(LEVELDIR):]
            if nplfdisp[0] == '/':
                nplfdisp = nplfdisp[1:]
        #
        #found = []
        npl = NERPsScript.load(nplf)
        i = 0
        while i < len(npl.instructions):
            instr = npl.instructions[i]
            #for i,instr in enumerate(npl.instructions):
            if instr.opcode.base is NERPsOpcode.Function:
                func = NERPS_FUNCS[instr.uint16]
                args = [None]*func.args.num_args
                for j in range(len(args)):
                    instrArg = npl.instructions[i + 1 + j]
                    if instrArg.opcode.base is NERPsOpcode.Function:
                        funcArg = NERPS_FUNCS[instrArg.uint16]
                        if funcArg.args is not NERPsArgs.Return0:
                            raise ValueError(f'Invalid argument instruction function: {instrArg}')
                        #argId = (NERPsOpcode.Function, funcArg.name)
                        argId = funcArg.name
                    elif instrArg.opcode.base is NERPsOpcode.Load:
                        #argId = (NERPsOpcode.Load, hex(instrArg.uint16))
                        #argId = hexint(instrArg.uint16)
                        argId = instrArg.uint16
                    else:
                        raise ValueError(f'Invalid argument instruction opcode: {instrArg}')
                    args[j] = argId
                    argsIndiv.setdefault(func.name, {})
                    argsIndiv[func.name][argId] = argsIndiv[func.name].setdefault(argId, 0) + 1
                argsId = tuple(args)
                argsFull.setdefault(func.name, {})
                argsFull[func.name][argsId] = argsFull[func.name].setdefault(argsId, 0) + 1
                calls[func.name] = calls.setdefault(func.name, 0) + 1
                i += func.args.num_args
            i += 1
    return (calls, argsFull, argsIndiv)


funcargs = scanfuncargs(LEVELDIR)

max((
    (k,max((
            ((kk,vv) if len(kk) else (kk,0)) for kk,vv in v.items()
        ), key=lambda x: x[1])) for k,v in funcargs[1].items()
), key=lambda x: x[1][1])



def write_tsv(file, funcargs=funcargs):
    import csv, io
    from collections import OrderedDict, UserList
    #
    if isinstance(file, str):
        with open(file, 'wt+', encoding='utf-8') as f:
            return write_tsv(f, funcargs=funcargs)
    #
    FIELD_NAMES = ('ID', 'Address', 'Return', 'Name', 'Arguments', 'Status', 'Notes')
    writer = csv.DictWriter(file, FIELD_NAMES, delimiter='\t', quotechar='"', lineterminator='\n')
    #
    rows = []
    for func_ in NERPS_FUNCS:
        func:NERPsFunction = func_
        #fargs = funcargs[func.name]
        address = int(func.func[4:], 16)
        dup_name = func.traits.dup_name
        constant = func.traits.constant
        funcId = func.id
        is_void = func.args.is_void
        num_args = func.args.num_args
        #
        id = f'\'{func.id:d}'
        addr = f'\'{int(func.func[4:], 16):08x}'
        ret = ('void' if func.args.is_void else ('return' if func.args.is_return else '-'))
        name = func.name
        if name.lower() in ('true','false','null'):
            name = f'\'{name}'
        args = '-'
        if func.args.num_args:
            args = ', '.join(f'arg{j+1}' for j in range(func.args.num_args))
        status = ''
        notes = ''
        #
        col = OrderedDict((('ID',id), ('Address',addr), ('Return',ret), ('Name',name), ('Arguments',args), ('Status',status), ('Notes',notes)))
        writer.writerow(col)
    file.flush()



TSVPATH = r"C:\<FILLMEIN>"
write_tsv(TSVPATH)

class NERPsMessages:
    _SPACES = ('\t', '\n', '\v', '\f', '\r', ' ')
    #_SPACES = (ord(b'\t'), ord(b'\n'), ord(b'\v'), ord(b'\f'), ord(b'\r'), ord(b' '))
    #
    lines:List[str]
    sounds:List[Tuple[str,str]]
    images:List[Tuple[str,str]]
    #
    def __init__(self, lines:Optional[Iterable[str]]=None, sounds:Optional[Iterable[Tuple[str,str]]]=None, images:Optional[Iterable[Tuple[str,str]]]=None):
        self.lines  = () if lines  is None else tuple(lines)
        self.sounds = () if sounds is None else tuple(sounds)
        self.images = () if images is None else tuple(images)
    #
    @classmethod
    def parse_property(cls, i:int, text:str, props:List[Tuple[str,str]]) -> int:
        # Parse length of key.
        start = i
        while i < len(text) and text[i] not in cls._SPACES:
            i += 1
        if i > start: # If key consists of at least one character.
            key = text[start:i]
            #
            # Skip whitespace/control chars and check for newline (only CR).
            carriage = False
            while i < len(text) and text[i] <= ' ':
                if text[i] == '\r':
                    carriage = True
                i += 1
            if not carriage: # If value is defined on same line (no CR).
                #
                # Parse length of value.
                start = i
                while i < len(text) and text[i] not in cls._SPACES:
                    i += 1
                if i > start: # If value consists of at least one character.
                    value = text[start:i]
                    #
                    props.append( (key, value) )
        #
        return i
    #
    @classmethod
    def parse_line(cls, i:int, text:str, lines:List[str]) -> int:
        # Parse length of line until control characters or EOF.
        start = i
        while i < len(text) and text[i] < ' ':
            i += 1
        if i > start: # If line consists of at least one character.
            line = text[start:i]
            line = line.replace('_', ' ') # Underscores are always replaced with spaces.
            #
            lines.append(line)
        #
        return i
    #
    @classmethod
    def load(cls, file:Union[str,bytes,bytearray,io.BufferedReader], encoding:str='ansi') -> 'NERPsMessages':
        if isinstance(file, str):
            with open(file, 'rb') as f:
                text = f.read()
        elif hasattr(file, 'read'):
            text = file.read()
        else:
            text = file # assume bytes/bytearray
        return cls.loads(text.decode(encoding))
        #
    @classmethod
    def loads(cls, text:str) -> 'NERPsMessages':
        lines  = [] # type: List[str]
        sounds = [] # type: List[Tuple[str,str]]
        images = [] # type: List[Tuple[str,str]]
        #
        newLine = False
        i = 0
        while i < len(text):
            if text[i] < ' ':
                # All control characters are newlines! Even tabs..... :'D
                newLine = True
                #
            elif newLine:
                # Define either an image, sound, or text line.
                # NOTE: Faulty logic allows both an image and text line to be assigned at once.
                #
                # Set to false to require another control character before we can parse another image/sound/line.
                newLine = False
                #
                if text[i] == ':':
                    # IMAGE DEFINITION: (with file extension)
                    #  `:myImageName  Path\To\imageFile.bmp`
                    i = cls.parse_property((i + 1), text, images)
                #
                # TODO: Should this be changed to `else if` to stop image and text definition on the same line?
                # NOTE: Logic for the above image block will NEVER leave i on a non-whitespace/control character if the block is run.
                if text[i] == '$':
                    # SOUND DEFINITION: (no file extension)
                    #  `$mySoundName  Path\To\soundFile`
                    i = cls.parse_property((i + 1), text, sounds)
                else:
                    # TEXT LINE DEFINITION:
                    #  `text goes here.`
                    #  `text_goes_here.`
                    #  `text goes_here. #refSoundName# <refImageName>...`
                    i = cls.parse_line(i, text, lines)
            #
            # When this += 1 occurs after parse_property and parse_line,
            #  it basically enforces the need for CRLF newlines.
            i += 1
        #
        return cls(lines=lines, sounds=sounds, images=images)
    #
    #
    @classmethod
    def parse_reference(cls, end:str, i:int, text:str, refs:List[Tuple[str,str]]) -> int:
        start = i
        while i < len(text):
            if text[i] == end:
                if i > start:
                    key = text[start:i]
                    for k,v in refs:
                        if key.lower() == k.lower():
                            refs.append( (key,v) )
                            break
                i += 1 # skip end character
                break
            else:
                i += 1
    #
    def get_message(self, index:int) -> Tuple[str, List[Tuple[str,str]], List[Tuple[str,str]]]:
        """get_message(i) -> (text, [(key,value),(sound,pairs)], [(key,value),(image,pairs)])
        """
        text = self.lines[index]
        #
        if not len(self.images) and not len(self.sounds):
            # No images or sounds, we can copy straight into the buffer, since there **shouldn't** be
            # anything to strip. Note that the number of these is determined by `:imageKey` and `$soundKey`
            # definitions elsewhere in the message file.
            return text
        else:
            # Go through and format text by picking out image/sound markers and only copying over plaintext to buffer.
            #
            # List of characters to join at the end.
            line   = [] # type: List[str]
            # #key#/<key> and matched value pairs
            sounds = [] # type: List[Tuple[str,str]]
            images = [] # type: List[Tuple[str,str]]
            #
            i = 0
            while i < len(text):
                if text[i] == '<':
                    # IMAGE REFERENCE:
                    #  `<imageKey>`
                    i = self.parse_reference('>', (i + 1), text, images)
                elif text[i] == '#':
                    # SOUND REFERENCE:
                    #  `#soundKey#`
                    i = self.parse_reference('#', (i + 1), text, sounds)
                else:
                    line.append(text[i])
                    i += 1
            #
            return (line, sounds, images)




class NERPsEngine:
    interpreter:NERPsScript
    messages:NERPsMessages
    registers:List[int] # len=8
    timers:List[float]  # len=4
    #
    def __init__(self):
        self.interpreter = NERPsScript()
        self.messages = NERPsMessages()
        self.registers = [0] * 8
        self.timers = [0.0] * 4
    #
    def execute(self, delta:float, *args, **kwargs) -> None:
        # Runtime registers (eax,ebx,neg,cmp) are always reset when executing.
        self.interpreter.reset()
        #
        while not self.interpreter.end_of_script:
            if self.interpreter.step(*args, **kwargs):
                break # True signals end of execution this tick.
        #
        self.end_execute(delta, *args, **kwargs)
    #
    def end_execute(self, delta:float, *args, **kwargs) -> None:
        # Complex stuff that hasn't been decompiled yet.
        # None of this changes the NERPsScript state.
        pass



class NERPsFunctions:
    @staticmethod
    def True_(stack:List[int]) -> int:
        return 1
    @staticmethod
    def False_(stack:List[int]) -> int:
        return 0
    #
    # Duplicates
    #
    Null = False_
    Stop = False_ # special handling
    GetCrystalsUsed   = False_ # implemented
    GetCrystalsStolen = False_ # implemented
    GetOreUsed   = False_ # implemented
    GetOreStolen = False_ # implemented
    #
    #SetGameCompleted = SetLevelCompleted
    #
    _End_Of_List_ = False_ # not a real function


    
MAXLEN = 48

NERPS_FUNCS = [
    NERPsFunc(id=0,    args=3, name='Stop',                                             func='FUN_004564d0'), # dup 'False' (hardcoded)
    NERPsFunc(id=1,    args=0, name='True',                                             func='FUN_00484e50', traits=NERPsTraits(constant=1)),
    NERPsFunc(id=2,    args=0, name='False',                                            func='FUN_004564d0', traits=NERPsTraits(constant=0)), # dup
    NERPsFunc(id=3,    args=0, name='Null',                                             func='FUN_004564d0', traits=NERPsTraits(constant=0, dup_name='False')), # dup 'False'
    NERPsFunc(id=4,    args=0, name='GetRandom',                                        func='FUN_00456450'),
    NERPsFunc(id=5,    args=0, name='GetRandom10',                                      func='FUN_00456470'),
    NERPsFunc(id=6,    args=0, name='GetRandom100',                                     func='FUN_00456490'),
    NERPsFunc(id=7,    args=0, name='GetRandomTrueFalse',                               func='FUN_00456460'),
    NERPsFunc(id=8,    args=3, name='SetLevelCompleted',                                func='FUN_00454e30'), # dup
    NERPsFunc(id=9,    args=3, name='SetLevelFail',                                     func='FUN_00454e40'),
    NERPsFunc(id=10,   args=3, name='SetGameCompleted',                                 func='FUN_00454e30'), # dup 'SetLevelCompleted'
    NERPsFunc(id=11,   args=3, name='SetGameFail',                                      func='FUN_00454e60'),
    NERPsFunc(id=12,   args=0, name='GetCrystalsPickedUp',                              func='FUN_004564b0'),
    NERPsFunc(id=13,   args=0, name='GetCrystalsCurrentlyStored',                       func='FUN_004564c0'),
    NERPsFunc(id=14,   args=0, name='GetCrystalsUsed',                                  func='FUN_004564d0', traits=NERPsTraits(constant=0, unimplemented=True, dup_name='False')), # dup 'False'
    NERPsFunc(id=15,   args=0, name='GetCrystalsStolen',                                func='FUN_004564d0', traits=NERPsTraits(constant=0, unimplemented=True, dup_name='False')), # dup 'False'
    NERPsFunc(id=16,   args=5, name='SetMessage',                                       func='FUN_00456990'),
    NERPsFunc(id=17,   args=0, name='GetR0',                                            func='FUN_00456510', traits=NERPsTraits(register=('Get','R',0))),
    NERPsFunc(id=18,   args=0, name='GetR1',                                            func='FUN_00456520', traits=NERPsTraits(register=('Get','R',1))),
    NERPsFunc(id=19,   args=0, name='GetR2',                                            func='FUN_00456530', traits=NERPsTraits(register=('Get','R',2))),
    NERPsFunc(id=20,   args=0, name='GetR3',                                            func='FUN_00456540', traits=NERPsTraits(register=('Get','R',3))),
    NERPsFunc(id=21,   args=0, name='GetR4',                                            func='FUN_00456550', traits=NERPsTraits(register=('Get','R',4))),
    NERPsFunc(id=22,   args=0, name='GetR5',                                            func='FUN_00456560', traits=NERPsTraits(register=('Get','R',5))),
    NERPsFunc(id=23,   args=0, name='GetR6',                                            func='FUN_00456570', traits=NERPsTraits(register=('Get','R',6))),
    NERPsFunc(id=24,   args=0, name='GetR7',                                            func='FUN_00456580', traits=NERPsTraits(register=('Get','R',7))),
    NERPsFunc(id=25,   args=4, name='SetR0',                                            func='FUN_00456790', traits=NERPsTraits(register=('Set','R',0))),
    NERPsFunc(id=26,   args=4, name='SetR1',                                            func='FUN_004567a0', traits=NERPsTraits(register=('Set','R',1))),
    NERPsFunc(id=27,   args=4, name='SetR2',                                            func='FUN_004567b0', traits=NERPsTraits(register=('Set','R',2))),
    NERPsFunc(id=28,   args=4, name='SetR3',                                            func='FUN_004567c0', traits=NERPsTraits(register=('Set','R',3))),
    NERPsFunc(id=29,   args=4, name='SetR4',                                            func='FUN_004567d0', traits=NERPsTraits(register=('Set','R',4))),
    NERPsFunc(id=30,   args=4, name='SetR5',                                            func='FUN_004567e0', traits=NERPsTraits(register=('Set','R',5))),
    NERPsFunc(id=31,   args=4, name='SetR6',                                            func='FUN_004567f0', traits=NERPsTraits(register=('Set','R',6))),
    NERPsFunc(id=32,   args=4, name='SetR7',                                            func='FUN_00456800', traits=NERPsTraits(register=('Set','R',7))),
    NERPsFunc(id=33,   args=4, name='AddR0',                                            func='FUN_00456590', traits=NERPsTraits(register=('Add','R',0))),
    NERPsFunc(id=34,   args=4, name='AddR1',                                            func='FUN_004565b0', traits=NERPsTraits(register=('Add','R',1))),
    NERPsFunc(id=35,   args=4, name='AddR2',                                            func='FUN_004565d0', traits=NERPsTraits(register=('Add','R',2))),
    NERPsFunc(id=36,   args=4, name='AddR3',                                            func='FUN_004565f0', traits=NERPsTraits(register=('Add','R',3))),
    NERPsFunc(id=37,   args=4, name='AddR4',                                            func='FUN_00456610', traits=NERPsTraits(register=('Add','R',4))),
    NERPsFunc(id=38,   args=4, name='AddR5',                                            func='FUN_00456630', traits=NERPsTraits(register=('Add','R',5))),
    NERPsFunc(id=39,   args=4, name='AddR6',                                            func='FUN_00456650', traits=NERPsTraits(register=('Add','R',6))),
    NERPsFunc(id=40,   args=4, name='AddR7',                                            func='FUN_00456670', traits=NERPsTraits(register=('Add','R',7))),
    NERPsFunc(id=41,   args=4, name='SubR0',                                            func='FUN_00456690', traits=NERPsTraits(register=('Sub','R',0))),
    NERPsFunc(id=42,   args=4, name='SubR1',                                            func='FUN_004566b0', traits=NERPsTraits(register=('Sub','R',1))),
    NERPsFunc(id=43,   args=4, name='SubR2',                                            func='FUN_004566d0', traits=NERPsTraits(register=('Sub','R',2))),
    NERPsFunc(id=44,   args=4, name='SubR3',                                            func='FUN_004566f0', traits=NERPsTraits(register=('Sub','R',3))),
    NERPsFunc(id=45,   args=4, name='SubR4',                                            func='FUN_00456710', traits=NERPsTraits(register=('Sub','R',4))),
    NERPsFunc(id=46,   args=4, name='SubR5',                                            func='FUN_00456730', traits=NERPsTraits(register=('Sub','R',5))),
    NERPsFunc(id=47,   args=4, name='SubR6',                                            func='FUN_00456750', traits=NERPsTraits(register=('Sub','R',6))),
    NERPsFunc(id=48,   args=4, name='SubR7',                                            func='FUN_00456770', traits=NERPsTraits(register=('Sub','R',7))),
    NERPsFunc(id=49,   args=4, name='SetMessagePermit',                                 func='FUN_004568b0'),
    NERPsFunc(id=50,   args=0, name='GetObjectiveShowing',                              func='FUN_00456ab0'),
    NERPsFunc(id=51,   args=0, name='GetTeleportIconClicked',                           func='FUN_00455df0'),
    NERPsFunc(id=52,   args=0, name='GetMiniFiguresOnLevel',                            func='FUN_00455dc0'),
    NERPsFunc(id=53,   args=0, name='GetBuildIconClicked',                              func='FUN_00455fb0'),
    NERPsFunc(id=54,   args=4, name='SetBuildIconClicked',                              func='FUN_004561d0'),
    NERPsFunc(id=55,   args=4, name='SetTeleportIconClicked',                           func='FUN_00456010'),
    NERPsFunc(id=56,   args=4, name='SetToolStoreIconClicked',                          func='FUN_00455bb0'),
    NERPsFunc(id=57,   args=0, name='GetToolStoreIconClicked',                          func='FUN_00455b00'),
    NERPsFunc(id=58,   args=4, name='FlashToolStoreIcon',                               func='FUN_00455cb0'),
    NERPsFunc(id=59,   args=4, name='FlashBuildIcon',                                   func='FUN_004563f0'),
    NERPsFunc(id=60,   args=4, name='FlashTeleportIcon',                                func='FUN_00456230'),
    NERPsFunc(id=61,   args=4, name='SetGoBackIconClicked',                             func='FUN_00454be0'),
    NERPsFunc(id=62,   args=0, name='GetGoBackIconClicked',                             func='FUN_00454c00'),
    NERPsFunc(id=63,   args=4, name='FlashGoBackIcon',                                  func='FUN_00454c20'),
    NERPsFunc(id=64,   args=4, name='SetDigIconClicked',                                func='FUN_004561b0'),
    NERPsFunc(id=65,   args=0, name='GetDigIconClicked',                                func='FUN_00455f90'),
    NERPsFunc(id=66,   args=4, name='FlashDigIcon',                                     func='FUN_004563d0'),
    NERPsFunc(id=67,   args=0, name='GetTimer0',                                        func='FUN_00453f60', traits=NERPsTraits(register=('Get','Timer',0))),
    NERPsFunc(id=68,   args=0, name='GetTimer1',                                        func='FUN_00453f70', traits=NERPsTraits(register=('Get','Timer',1))),
    NERPsFunc(id=69,   args=0, name='GetTimer2',                                        func='FUN_00453f80', traits=NERPsTraits(register=('Get','Timer',2))),
    NERPsFunc(id=70,   args=0, name='GetTimer3',                                        func='FUN_00453f90', traits=NERPsTraits(register=('Get','Timer',3))),
    NERPsFunc(id=71,   args=4, name='SetTimer0',                                        func='FUN_00453fa0', traits=NERPsTraits(register=('Set','Timer',0))),
    NERPsFunc(id=72,   args=4, name='SetTimer1',                                        func='FUN_00453fd0', traits=NERPsTraits(register=('Set','Timer',1))),
    NERPsFunc(id=73,   args=4, name='SetTimer2',                                        func='FUN_00454000', traits=NERPsTraits(register=('Set','Timer',2))),
    NERPsFunc(id=74,   args=4, name='SetTimer3',                                        func='FUN_00454030', traits=NERPsTraits(register=('Set','Timer',3))),
    NERPsFunc(id=75,   args=0, name='GetBarracksBuilt',                                 func='FUN_00455920'),
    NERPsFunc(id=76,   args=0, name='GetOreRefineriesBuilt',                            func='FUN_00455dd0'),
    NERPsFunc(id=77,   args=0, name='GetToolStoresBuilt',                               func='FUN_00455960'),
    NERPsFunc(id=78,   args=0, name='GetStudCount',                                     func='FUN_00455d60'),
    NERPsFunc(id=79,   args=0, name='GetTeleportsBuilt',                                func='FUN_00455980'),
    NERPsFunc(id=80,   args=0, name='GetMiniFigureSelected',                            func='FUN_004550d0'),
    NERPsFunc(id=81,   args=0, name='GetSmallDiggerSelected',                           func='FUN_00455140'),
    NERPsFunc(id=82,   args=0, name='GetMiniFigureinSmallDigger',                       func='FUN_004556a0'),
    NERPsFunc(id=83,   args=0, name='GetTrainFlags',                                    func='FUN_00456820'),
    NERPsFunc(id=84,   args=4, name='SetTrainFlags',                                    func='FUN_00456830'),
    NERPsFunc(id=85,   args=5, name='SetIconPos',                                       func='FUN_00454dd0'),
    NERPsFunc(id=86,   args=4, name='SetIconSpace',                                     func='FUN_00454e10'),
    NERPsFunc(id=87,   args=4, name='SetIconWidth',                                     func='FUN_00454e20'),
    NERPsFunc(id=88,   args=4, name='SetMessageWait',                                   func='FUN_00456920'),
    NERPsFunc(id=89,   args=0, name='GetMountIconClicked',                              func='FUN_00455e30'),
    NERPsFunc(id=90,   args=4, name='SetMountIconClicked',                              func='FUN_00456190'),
    NERPsFunc(id=91,   args=4, name='FlashMountIcon',                                   func='FUN_00456270'),
    NERPsFunc(id=92,   args=5, name='SetTutorialPointer',                               func='FUN_00454e70'),
    NERPsFunc(id=93,   args=0, name='GetTutorialFlags',                                 func='FUN_00456500'),
    NERPsFunc(id=94,   args=4, name='SetTutorialFlags',                                 func='FUN_00456810'),
    NERPsFunc(id=95,   args=5, name='SetRockMonster',                                   func='FUN_00454af0'),
    NERPsFunc(id=96,   args=0, name='GetOrePickedUp',                                   func='FUN_004564e0'),
    NERPsFunc(id=97,   args=0, name='GetOreCurrentlyStored',                            func='FUN_004564f0'),
    NERPsFunc(id=98,   args=0, name='GetOreUsed',                                       func='FUN_004564d0', traits=NERPsTraits(constant=0, unimplemented=True, dup_name='False')), # dup 'False'
    NERPsFunc(id=99,   args=0, name='GetOreStolen',                                     func='FUN_004564d0', traits=NERPsTraits(constant=0, unimplemented=True, dup_name='False')), # dup 'False'
    NERPsFunc(id=100,  args=0, name='GetCrystalRefineriesBuilt',                        func='FUN_00455de0'),
    NERPsFunc(id=101,  args=4, name='FlashLayPathIcon',                                 func='FUN_00456410'),
    NERPsFunc(id=102,  args=4, name='SetLayPathIconClicked',                            func='FUN_004561f0'),
    NERPsFunc(id=103,  args=0, name='GetLayPathIconClicked',                            func='FUN_00455fd0'),
    NERPsFunc(id=104,  args=0, name='GetTeleportPadIconClicked',                        func='FUN_00455b20'),
    NERPsFunc(id=105,  args=4, name='SetTeleportPadIconClicked',                        func='FUN_00455bf0'),
    NERPsFunc(id=106,  args=4, name='FlashTeleportPadIcon',                             func='FUN_00455cf0'),
    NERPsFunc(id=107,  args=0, name='GetMessageTimer',                                  func='FUN_00456980'),
    NERPsFunc(id=108,  args=6, name='SetMessageTimerValues',                            func='FUN_00456930'),
    NERPsFunc(id=109,  args=1, name='GetTutorialBlockClicks',                           func='FUN_00455480'),
    NERPsFunc(id=110,  args=5, name='SetTutorialBlockClicks',                           func='FUN_00454f40'),
    NERPsFunc(id=111,  args=1, name='GetTutorialCrystals',                              func='FUN_00455420'),
    NERPsFunc(id=112,  args=5, name='SetTutorialCrystals',                              func='FUN_00454fd0'),
    NERPsFunc(id=113,  args=0, name='GetPathsBuilt',                                    func='FUN_00455d50'),
    NERPsFunc(id=114,  args=1, name='GetTutorialBlockIsGround',                         func='FUN_00457620'),
    NERPsFunc(id=115,  args=4, name='SetCameraGotoTutorial',                            func='FUN_004575a0'),
    NERPsFunc(id=116,  args=4, name='FlashDynamiteIcon',                                func='FUN_00456250'),
    NERPsFunc(id=117,  args=0, name='GetDynamiteClicked',                               func='FUN_00455e10'),
    NERPsFunc(id=118,  args=4, name='SetDynamiteClicked',                               func='FUN_00456030'),
    NERPsFunc(id=119,  args=4, name='AddPoweredCrystals',                               func='FUN_00455390'),
    NERPsFunc(id=120,  args=0, name='GetGraniteGrinderSelected',                        func='FUN_00455260'),
    NERPsFunc(id=121,  args=0, name='GetChromeCrusherSelected',                         func='FUN_004552c0'),
    NERPsFunc(id=122,  args=1, name='GetTutorialBlockIsPath',                           func='FUN_00457660'),
    NERPsFunc(id=123,  args=0, name='GetGunstationIconClicked',                         func='FUN_00455b10'),
    NERPsFunc(id=124,  args=4, name='SetGunstationIconClicked',                         func='FUN_00455bd0'),
    NERPsFunc(id=125,  args=4, name='FlashGunstationIcon',                              func='FUN_00455cd0'),
    NERPsFunc(id=126,  args=0, name='GetGunstationsBuilt',                              func='FUN_00455970'),
    NERPsFunc(id=127,  args=5, name='SetOreAtIconPositions',                            func='FUN_00455050'),
    NERPsFunc(id=128,  args=0, name='GetVehicleTeleportsBuilt',                         func='FUN_00455990'),
    NERPsFunc(id=129,  args=0, name='GetVehicleTransportIconClicked',                   func='FUN_00455b30'),
    NERPsFunc(id=130,  args=4, name='SetVehicleTransportIconClicked',                   func='FUN_00455c10'),
    NERPsFunc(id=131,  args=4, name='FlashVehicleTransportIcon',                        func='FUN_00455d10'),
    NERPsFunc(id=132,  args=0, name='GetUpgradeStationIconClicked',                     func='FUN_00455b40'),
    NERPsFunc(id=133,  args=4, name='SetUpgradeStationIconClicked',                     func='FUN_00455c30'),
    NERPsFunc(id=134,  args=4, name='FlashUpgradeStationIcon',                          func='FUN_00455d30'),
    NERPsFunc(id=135,  args=0, name='GetUpgradeStationsBuilt',                          func='FUN_004559a0'),
    NERPsFunc(id=136,  args=5, name='SetTutorialBlockIsGround',                         func='FUN_004576a0'),
    NERPsFunc(id=137,  args=5, name='SetTutorialBlockIsPath',                           func='FUN_004576e0'),
    NERPsFunc(id=138,  args=4, name='CameraLockOnObject',                               func='FUN_00454310'),
    NERPsFunc(id=139,  args=3, name='CameraUnlock',                                     func='FUN_00454330'),
    NERPsFunc(id=140,  args=4, name='CameraZoomIn',                                     func='FUN_00454350'),
    NERPsFunc(id=141,  args=4, name='CameraZoomOut',                                    func='FUN_004543d0'),
    NERPsFunc(id=142,  args=4, name='CameraRotate',                                     func='FUN_00454440'),
    NERPsFunc(id=143,  args=1, name='GetCameraAtTutorial',                              func='FUN_004575e0'),
    NERPsFunc(id=144,  args=0, name='GetSelectedRecordObject',                          func='FUN_004544e0'),
    NERPsFunc(id=145,  args=0, name='GetSmallHelicopterSelected',                       func='FUN_00455200'),
    NERPsFunc(id=146,  args=0, name='GetRapidRiderSelected',                            func='FUN_004551a0'),
    NERPsFunc(id=147,  args=0, name='GetMiniFigureinRapidRider',                        func='FUN_004556b0'),
    NERPsFunc(id=148,  args=0, name='GetDismountIconClicked',                           func='FUN_00455f70'),
    NERPsFunc(id=149,  args=4, name='SetDismountIconClicked',                           func='FUN_00456150'),
    NERPsFunc(id=150,  args=4, name='FlashDismountIcon',                                func='FUN_00456310'),
    NERPsFunc(id=151,  args=0, name='GetGetToolIconClicked',                            func='FUN_00455e90'),
    NERPsFunc(id=152,  args=4, name='SetGetToolIconClicked',                            func='FUN_004560b0'),
    NERPsFunc(id=153,  args=4, name='FlashGetToolIcon',                                 func='FUN_00456330'),
    NERPsFunc(id=154,  args=0, name='GetAnyKeyPressed',                                 func='FUN_00454dc0'),
    NERPsFunc(id=155,  args=4, name='SetPauseGame',                                     func='FUN_00454da0'),
    NERPsFunc(id=156,  args=0, name='GetGetLaserIconClicked',                           func='FUN_00455f50'),
    NERPsFunc(id=157,  args=4, name='SetGetLaserIconClicked',                           func='FUN_004560f0'),
    NERPsFunc(id=158,  args=4, name='FlashGetLaserIcon',                                func='FUN_00456370'),
    NERPsFunc(id=159,  args=4, name='SetRockMonsterAtTutorial',                         func='FUN_00457560'),
    NERPsFunc(id=160,  args=0, name='GetCallToArmsButtonClicked',                       func='FUN_00454ae0'),
    NERPsFunc(id=161,  args=0, name='GetRockMonstersDestroyed',                         func='FUN_00454b30'),
    NERPsFunc(id=162,  args=4, name='SetGetPusherIconClicked',                          func='FUN_00456110'),
    NERPsFunc(id=163,  args=0, name='GetGetPusherIconClicked',                          func='FUN_00455eb0'),
    NERPsFunc(id=164,  args=4, name='FlashGetPusherIcon',                               func='FUN_00456390'),
    NERPsFunc(id=165,  args=0, name='GetRockMonsterRunningAway',                        func='FUN_00454c40'),
    NERPsFunc(id=166,  args=4, name='SetCallToArms',                                    func='FUN_00454ac0'),
    NERPsFunc(id=167,  args=4, name='FlashPowerStationIcon',                            func='FUN_00455c90'),
    NERPsFunc(id=168,  args=4, name='SetPowerstationIconClicked',                       func='FUN_00455b90'),
    NERPsFunc(id=169,  args=0, name='GetPowerstationIconClicked',                       func='FUN_00455af0'),
    NERPsFunc(id=170,  args=0, name='GetPowerstationsBuilt',                            func='FUN_00455950'),
    NERPsFunc(id=171,  args=4, name='SetAttackDefer',                                   func='FUN_00454aa0'),
    NERPsFunc(id=172,  args=4, name='SetRockMonsterPainThreshold',                      func='FUN_00454d20'),
    NERPsFunc(id=173,  args=4, name='SetRockMonsterHealth',                             func='FUN_00454d60'),
    NERPsFunc(id=174,  args=5, name='SetGameSpeed',                                     func='FUN_00453b60'),
    NERPsFunc(id=175,  args=4, name='FlashBarracksIcon',                                func='FUN_00455c50'),
    NERPsFunc(id=176,  args=4, name='SetBarracksIconClicked',                           func='FUN_00455b50'),
    NERPsFunc(id=177,  args=0, name='GetBarracksIconClicked',                           func='FUN_00455ad0'),
    NERPsFunc(id=178,  args=1, name='GetRecordObjectAtTutorial',                        func='FUN_004547f0'),
    NERPsFunc(id=179,  args=0, name='GetHiddenObjectsFound',                            func='FUN_00454b60'),
    NERPsFunc(id=180,  args=4, name='SetHiddenObjectsFound',                            func='FUN_00454b70'),
    NERPsFunc(id=181,  args=0, name='GetOxygenLevel',                                   func='FUN_004549e0'),
    NERPsFunc(id=182,  args=4, name='FlashGeodomeIcon',                                 func='FUN_00455c70'),
    NERPsFunc(id=183,  args=0, name='GetGeodomeIconClicked',                            func='FUN_00455ae0'),
    NERPsFunc(id=184,  args=4, name='SetGeodomeIconClicked',                            func='FUN_00455b70'),
    NERPsFunc(id=185,  args=0, name='GetGeodomeBuilt',                                  func='FUN_00455940'),
    NERPsFunc(id=186,  args=4, name='AddStoredOre',                                     func='FUN_004553c0'),
    NERPsFunc(id=187,  args=3, name='GenerateSlug',                                     func='FUN_00454a60'),
    NERPsFunc(id=188,  args=0, name='GetSlugsOnLevel',                                  func='FUN_00455db0'),
    NERPsFunc(id=189,  args=0, name='GetMonstersOnLevel',                               func='FUN_00456840'),
    NERPsFunc(id=190,  args=5, name='SetCongregationAtTutorial',                        func='FUN_00457520'),
    NERPsFunc(id=191,  args=4, name='SetObjectiveSwitch',                               func='FUN_00456a80'),
    NERPsFunc(id=192,  args=0, name='GetObjectiveSwitch',                               func='FUN_00456a90'),
    NERPsFunc(id=193,  args=0, name='GetGraniteGrindersOnLevel',                        func='FUN_00455d80'),
    NERPsFunc(id=194,  args=0, name='GetSmallDiggersOnLevel',                           func='FUN_00455da0'),
    NERPsFunc(id=195,  args=0, name='GetDocksBuilt',                                    func='FUN_00455930'),
    NERPsFunc(id=196,  args=0, name='GetRapidRidersOnLevel',                            func='FUN_00455d90'),
    NERPsFunc(id=197,  args=1, name='GetUnitAtBlock',                                   func='FUN_00457720'),
    NERPsFunc(id=198,  args=0, name='GetSmallHelicoptersOnLevel',                       func='FUN_00455d70'),
    NERPsFunc(id=199,  args=1, name='GetRecordObjectAmountAtTutorial',                  func='FUN_00454860'),
    NERPsFunc(id=200,  args=3, name='AdvanceMessage',                                   func='FUN_00453d10'),
    NERPsFunc(id=201,  args=4, name='AllowCameraMovement',                              func='FUN_00453d30'),
    NERPsFunc(id=202,  args=3, name='ClickOnlyObjects',                                 func='FUN_00453d50'),
    NERPsFunc(id=203,  args=3, name='ClickOnlyMap',                                     func='FUN_00453d80'),
    NERPsFunc(id=204,  args=3, name='ClickOnlyIcon',                                    func='FUN_00453db0'),
    NERPsFunc(id=205,  args=3, name='DisallowAll',                                      func='FUN_00453e10'),
    NERPsFunc(id=206,  args=4, name='SupressArrow',                                     func='FUN_00453cd0'),
    NERPsFunc(id=207,  args=0, name='GetMiniFigureinGraniteGrinder',                    func='FUN_00455680'),
    NERPsFunc(id=208,  args=0, name='GetMiniFigureinChromeCrusher',                     func='FUN_00455690'),
    NERPsFunc(id=209,  args=0, name='GetMessagesAreUpToDate',                           func='FUN_00453cb0'),
    NERPsFunc(id=210,  args=4, name='SetCrystalPriority',                               func='FUN_00454530'),
    NERPsFunc(id=211,  args=4, name='MakeSomeoneOnThisBlockPickUpSomethingOnThisBlock', func='FUN_004573f0'),
    NERPsFunc(id=212,  args=4, name='SetTrainIconClicked',                              func='FUN_00456050'),
    NERPsFunc(id=213,  args=0, name='GetTrainIconClicked',                              func='FUN_00455e50'),
    NERPsFunc(id=214,  args=4, name='FlashTrainIcon',                                   func='FUN_00456290'),
    NERPsFunc(id=215,  args=4, name='SetTrainDriverIconClicked',                        func='FUN_00456070'),
    NERPsFunc(id=216,  args=0, name='GetTrainDriverIconClicked',                        func='FUN_00455f30'),
    NERPsFunc(id=217,  args=4, name='FlashTrainDriverIcon',                             func='FUN_004562b0'),
    NERPsFunc(id=218,  args=4, name='SetTrainPilotIconClicked',                         func='FUN_00456170'),
    NERPsFunc(id=219,  args=0, name='GetTrainPilotIconClicked',                         func='FUN_00455f10'),
    NERPsFunc(id=220,  args=4, name='FlashTrainPilotIcon',                              func='FUN_004562d0'),
    NERPsFunc(id=221,  args=4, name='SetTrainSailorIconClicked',                        func='FUN_00456090'),
    NERPsFunc(id=222,  args=0, name='GetTrainSailorIconClicked',                        func='FUN_00455ef0'),
    NERPsFunc(id=223,  args=4, name='FlashTrainSailorIcon',                             func='FUN_004562f0'),
    NERPsFunc(id=224,  args=0, name='GetSmallTruckSelected',                            func='FUN_004550e0'),
    NERPsFunc(id=225,  args=0, name='GetMiniFigureinSmallTruck',                        func='FUN_004556c0'),
    NERPsFunc(id=226,  args=0, name='GetMiniFigureinSmallHelicopter',                   func='FUN_004556d0'),
    NERPsFunc(id=227,  args=4, name='SetBarracksLevel',                                 func='FUN_004556e0'),
    NERPsFunc(id=228,  args=4, name='SetDocksLevel',                                    func='FUN_00455700'),
    NERPsFunc(id=229,  args=4, name='SetGeoDomeLevel',                                  func='FUN_00455720'),
    NERPsFunc(id=230,  args=4, name='SetPowerstationLevel',                             func='FUN_00455740'),
    NERPsFunc(id=231,  args=4, name='SetToolStoreLevel',                                func='FUN_00455760'),
    NERPsFunc(id=232,  args=4, name='SetGunstationLevel',                               func='FUN_00455780'),
    NERPsFunc(id=233,  args=4, name='SetTeleportPadLevel',                              func='FUN_004557a0'),
    NERPsFunc(id=234,  args=4, name='SetSuperTeleportLevel',                            func='FUN_004557c0'),
    NERPsFunc(id=235,  args=4, name='SetUpgradeStationLevel',                           func='FUN_004557e0'),
    NERPsFunc(id=236,  args=0, name='GetBarracksSelected',                              func='FUN_00455800'),
    NERPsFunc(id=237,  args=0, name='GetDocksSelected',                                 func='FUN_00455810'),
    NERPsFunc(id=238,  args=0, name='GetGeoDomeSelected',                               func='FUN_00455820'),
    NERPsFunc(id=239,  args=0, name='GetPowerstationSelected',                          func='FUN_00455830'),
    NERPsFunc(id=240,  args=0, name='GetToolStoreSelected',                             func='FUN_00455840'),
    NERPsFunc(id=241,  args=0, name='GetGunstationSelected',                            func='FUN_00455850'),
    NERPsFunc(id=242,  args=0, name='GetTeleportPadSelected',                           func='FUN_00455860'),
    NERPsFunc(id=243,  args=0, name='GetSuperTeleportSelected',                         func='FUN_00455870'),
    NERPsFunc(id=244,  args=0, name='GetUpgradeStationSelected',                        func='FUN_00455880'),
    NERPsFunc(id=245,  args=4, name='SetUpgradeBuildingIconClicked',                    func='FUN_00454b80'),
    NERPsFunc(id=246,  args=0, name='GetUpgradeBuildingIconClicked',                    func='FUN_00454ba0'),
    NERPsFunc(id=247,  args=4, name='FlashUpgradeBuildingIcon',                         func='FUN_00454bc0'),
    NERPsFunc(id=248,  args=0, name='GetBuildingsTeleported',                           func='FUN_00456880'),
    NERPsFunc(id=249,  args=4, name='SetBuildingsTeleported',                           func='FUN_00456890'),
    NERPsFunc(id=250,  args=4, name='CameraLockOnMonster',                              func='FUN_004542a0'),
    NERPsFunc(id=251,  args=4, name='SetMonsterAttackPowerstation',                     func='FUN_00454550'),
    NERPsFunc(id=252,  args=3, name='ClickOnlyCalltoarms',                              func='FUN_00453de0'),
    NERPsFunc(id=253,  args=4, name='FlashCallToArmsIcon',                              func='FUN_00453e40'),
    NERPsFunc(id=254,  args=4, name='SetRecordObjectPointer',                           func='FUN_004549c0'),
    NERPsFunc(id=255,  args=0, name='GetGetSonicBlasterIconClicked',                    func='FUN_00455ed0'),
    NERPsFunc(id=256,  args=4, name='SetGetSonicBlasterIconClicked',                    func='FUN_00456130'),
    NERPsFunc(id=257,  args=4, name='FlashGetSonicBlasterIcon',                         func='FUN_004563b0'),
    NERPsFunc(id=258,  args=0, name='GetDropSonicBlasterIconClicked',                   func='FUN_00455e70'),
    NERPsFunc(id=259,  args=4, name='SetDropSonicBlasterIconClicked',                   func='FUN_004560d0'),
    NERPsFunc(id=260,  args=4, name='FlashDropSonicBlasterIcon',                        func='FUN_00456350'),
    NERPsFunc(id=261,  args=1, name='GetMonsterAtTutorial',                             func='FUN_00457760'),
    NERPsFunc(id=262,  args=4, name='SetMonsterAttackNowt',                             func='FUN_00454660'),
    NERPsFunc(id=263,  args=0, name='GetPlaceFenceIconClicked',                         func='FUN_00455ff0'),
    NERPsFunc(id=264,  args=4, name='SetPlaceFenceIconClicked',                         func='FUN_00456210'),
    NERPsFunc(id=265,  args=4, name='FlashPlaceFenceIcon',                              func='FUN_00456430'),
    NERPsFunc(id=266,  args=0, name='GetLevel1BarracksBuilt',                           func='FUN_004559b0'),
    NERPsFunc(id=267,  args=0, name='GetLevel1DocksBuilt',                              func='FUN_004559c0'),
    NERPsFunc(id=268,  args=0, name='GetLevel1GeodomeBuilt',                            func='FUN_004559d0'),
    NERPsFunc(id=269,  args=0, name='GetLevel1PowerstationsBuilt',                      func='FUN_004559e0'),
    NERPsFunc(id=270,  args=0, name='GetLevel1ToolStoresBuilt',                         func='FUN_004559f0'),
    NERPsFunc(id=271,  args=0, name='GetLevel1GunstationsBuilt',                        func='FUN_00455a00'),
    NERPsFunc(id=272,  args=0, name='GetLevel1TeleportsBuilt',                          func='FUN_00455a10'),
    NERPsFunc(id=273,  args=0, name='GetLevel1VehicleTeleportsBuilt',                   func='FUN_00455a20'),
    NERPsFunc(id=274,  args=0, name='GetLevel1UpgradeStationsBuilt',                    func='FUN_00455a30'),
    NERPsFunc(id=275,  args=0, name='GetLevel2BarracksBuilt',                           func='FUN_00455a40'),
    NERPsFunc(id=276,  args=0, name='GetLevel2DocksBuilt',                              func='FUN_00455a50'),
    NERPsFunc(id=277,  args=0, name='GetLevel2GeodomeBuilt',                            func='FUN_00455a60'),
    NERPsFunc(id=278,  args=0, name='GetLevel2PowerstationsBuilt',                      func='FUN_00455a70'),
    NERPsFunc(id=279,  args=0, name='GetLevel2ToolStoresBuilt',                         func='FUN_00455a80'),
    NERPsFunc(id=280,  args=0, name='GetLevel2GunstationsBuilt',                        func='FUN_00455a90'),
    NERPsFunc(id=281,  args=0, name='GetLevel2TeleportsBuilt',                          func='FUN_00455aa0'),
    NERPsFunc(id=282,  args=0, name='GetLevel2VehicleTeleportsBuilt',                   func='FUN_00455ab0'),
    NERPsFunc(id=283,  args=0, name='GetLevel2UpgradeStationsBuilt',                    func='FUN_00455ac0'),
    NERPsFunc(id=284,  args=0, name='GetPoweredBarracksBuilt',                          func='FUN_00455890'),
    NERPsFunc(id=285,  args=0, name='GetPoweredDocksBuilt',                             func='FUN_004558a0'),
    NERPsFunc(id=286,  args=0, name='GetPoweredGeodomeBuilt',                           func='FUN_004558b0'),
    NERPsFunc(id=287,  args=0, name='GetPoweredPowerstationsBuilt',                     func='FUN_004558c0'),
    NERPsFunc(id=288,  args=0, name='GetPoweredToolStoresBuilt',                        func='FUN_004558d0'),
    NERPsFunc(id=289,  args=0, name='GetPoweredGunstationsBuilt',                       func='FUN_004558e0'),
    NERPsFunc(id=290,  args=0, name='GetPoweredTeleportsBuilt',                         func='FUN_004558f0'),
    NERPsFunc(id=291,  args=0, name='GetPoweredVehicleTeleportsBuilt',                  func='FUN_00455900'),
    NERPsFunc(id=292,  args=0, name='GetPoweredUpgradeStationsBuilt',                   func='FUN_00455910'),
    NERPsFunc(id=293,  args=7, name='**End Of List**',                                  func='FUN_004564d0', traits=NERPsTraits(constant=0, unimplemented=True, dup_name='False')), # dup 'False'
]

