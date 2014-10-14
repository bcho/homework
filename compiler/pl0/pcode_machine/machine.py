# coding: utf-8

'''
# P-Code Machine

### Reference:

- http://cs2.uco.edu/~trt/cs4173/pspec.pdf
- https://github.com/lkesteloot/turbopascal
'''

from collections import namedtuple


# ## Basic Routines

class ExecuteError(RuntimeError):
    '''Machine execute error.'''


def panic(ExceptionClass=ExecuteError, message=None):
    message = message or 'error'

    exception = ExceptionClass(message)

    raise exception


# ## Instructions

'''
### Instructions Format

31                      15          7           0
+-----------------------+-----------+-----------+
| op2                   | op1       | opcode    |
+-----------------------+-----------+-----------+
'''

OPCODE_BITS = 8
OP1_BITS = 8
OP2_BTIS = 16

OPCODE_MASK = (1 << OPCODE_BITS) - 1
GET_OPCODE = lambda x: int(x) & OPCODE_MASK
OP1_MASK = (1 << OP1_BITS) - 1
GET_OP1 = lambda x: (int(x) >> (OPCODE_BITS)) & OP1_MASK
OP2_MASK = (1 << OP2_BTIS) - 1
GET_OP2 = lambda x: (int(x) >> (OPCODE_BITS + OP1_BITS)) & OP2_MASK


# ### Instructions
Instruction = namedtuple('Instruction', ['name', 'opcode', 'comments'])

insts_list = [
    # Subprogram linkage ops.
    Instruction('CUP', 0x00, 'Call user procedure'),
    Instruction('CSP', 0x01, 'Call standard procedure'),
    Instruction('ENT', 0x02, 'Procedure entry'),
    Instruction('MST', 0x03, 'Mark stack'),
    Instruction('RTN', 0x04, 'Return'),

    # Comparaion ops.
    Instruction('EQU', 0x05, 'Equality comparison'),
    Instruction('NEQ', 0x06, 'Inequality comparison'),
    Instruction('GRT', 0x07, 'Greater than comparison'),
    Instruction('GEQ', 0x08, 'Greater than or equal comparison'),
    Instruction('LES', 0x09, 'Less than comparison'),
    Instruction('LEQ', 0x0A, 'Less than or equal comparison'),

    # Arithmetic ops.
    Instruction('ADI', 0x0B, 'Integer addition'),
    Instruction('SBI', 0x0C, 'Integer subtraction'),
    Instruction('NGI', 0x0D, 'Integer sign inversion'),
    Instruction('MPI', 0x0E, 'Integer multiplication'),
    Instruction('DVI', 0x0F, 'Integer divison'),
    Instruction('MOD', 0x10, 'Integer modulo'),
    Instruction('ABI', 0x11, 'Integer absolute value'),
    Instruction('SQI', 0x12, 'Integer square'),
    Instruction('INC', 0x13, 'Increment'),
    Instruction('DEC', 0x14, 'Decrement'),
    Instruction('ABR', 0x15, 'Real addition'),
    Instruction('SBR', 0x16, 'Real subtraction'),
    Instruction('NGR', 0x17, 'Real sign inversion'),
    Instruction('MPR', 0x18, 'Real multiplication'),
    Instruction('DVR', 0x19, 'Real divison'),
    Instruction('ABR', 0x1A, 'Real absolute value'),
    Instruction('SQR', 0x1B, 'Real square'),

    # Boolean ops.
    Instruction('IOR', 0x1C, 'Inclusive OR'),
    Instruction('AND', 0x1D, 'And'),
    Instruction('XOR', 0x1E, 'Exclusive OR'),
    Instruction('NOT', 0x1F, 'Complement'),

    # Set ops. (Not implement yet.)
    Instruction('INN', 0x20, 'Set membership'),
    Instruction('UNI', 0x21, 'Set union'),
    Instruction('INT', 0x22, 'Set intersection'),
    Instruction('DIF', 0x23, 'Set difference'),
    Instruction('CMP', 0x24, 'Comlement'),
    Instruction('SGS', 0x25, 'Generate singleton set'),

    # Jump ops.
    Instruction('UJP', 0x26, 'Unconditional jump'),
    Instruction('XJP', 0x27, 'Indexed jump'),
    Instruction('FJP', 0x28, 'False jump'),
    Instruction('TJP', 0x29, 'True jump'),

    # Conversion ops.
    Instruction('FLT', 0x2A, 'Float top of stack'),
    Instruction('FLO', 0x2B, 'Float next to top of stack'),
    Instruction('TRC', 0x2C, 'Truncate'),
    Instruction('MD',  0x2D, 'Round'),
    Instruction('CHR', 0x2E, 'Convert to character'),
    Instruction('ORD', 0x2F, 'Convert to integer'),

    # Data reference ops.
    Instruction('LDA', 0x31, 'Load address of data'),
    Instruction('LDC', 0x32, 'Load constant'),
    Instruction('LDI', 0x33, 'Load indrect'),
    Instruction('LVA', 0x34, 'Load value (address)'),
    Instruction('LVB', 0x35, 'Load value (boolean)'),
    Instruction('LVC', 0x36, 'Load value (character)'),
    Instruction('LVI', 0x37, 'Load value (integer)'),
    Instruction('LVR', 0x38, 'Load value (float)'),
    Instruction('LVS', 0x39, 'Load value (set)'),
    Instruction('STI', 0x3A, 'Store indirect'),
    Instruction('IXA', 0x3B, 'Compute indexed address')
]

# Instruction name-ed map
instructions = {i.name: i for i in insts_list}


# ## Registers

Register = namedtuple('Register', ['name', 'value', 'comments'])

registers_list = [
    Register('sp', 0x00, 'Stack pointer'),
    Register('ep', 0x01, 'Extreme pointer'),  # Won't be used here.
    Register('mp', 0x02, 'Mark pointer'),
    Register('pc', 0x03, 'Program pointer'),
    Register('nc', 0x04, 'New pointer')
]

# Register name-ed map
registers = {i.name: i for i in registers_list}


# ## Data Types

DataType = namedtuple('DataType', ['type', 'value', 'name', 'converter'])

data_types_list = [
    DataType('a', 0x00, 'address', lambda x: int(x)),  # Address is in decimal!
    DataType('b', 0x01, 'boolean', lambda x: bool(x)),
    DataType('c', 0x02, 'char', lambda x: str(x)[0]),
    DataType('i', 0x03, 'integer', lambda x: int(x)),
    DataType('r', 0x04, 'real', lambda x: float(x)),
    DataType('s', 0x05, 'string', lambda x: str(x)),
    DataType('t', 0x06, 'set', lambda x: set(x)),  # TODO review converter
    DataType('x', 0x07, 'dynamic type', lambda x: x)
]

# Datatypes type-ed map
data_types = {i.type: i for i in data_types_list}


# ## Builtin Functions.

Builtin = namedtuple('Builtin', ['name', 'opcode', 'comments', 'fn'])

# TODO implement the builtins.
builtin_default_fn = lambda: panic(NotImplementedError)

builtins_list = [
    Builtin('rdb', 0x00, 'Read boolean', builtin_default_fn),
    Builtin('rdc', 0x01, 'Read char', builtin_default_fn),
    Builtin('rdi', 0x02, 'Read integer', builtin_default_fn),
    Builtin('rdr', 0x03, 'Read real', builtin_default_fn),
    Builtin('rln', 0x04, 'Read line', builtin_default_fn),
    Builtin('wrb', 0x05, 'Write boolean', builtin_default_fn),
    Builtin('wrc', 0x06, 'Write char', builtin_default_fn),
    Builtin('wri', 0x07, 'Write integer', builtin_default_fn),
    Builtin('wre', 0x08, 'Write real, exponential format', builtin_default_fn),
    Builtin('wrf', 0x09, 'Write float, fixed format', builtin_default_fn),
    Builtin('wrs', 0x0A, 'Write string', builtin_default_fn),
    Builtin('wln', 0x0B, 'Write line', builtin_default_fn),
    Builtin('sqt', 0x0C, 'Square root', builtin_default_fn),
    Builtin('ln',  0x0D, 'Natural logarithm', builtin_default_fn),
    Builtin('exp', 0x0E, 'Exponentiation', builtin_default_fn)
]

builtins = {i.name: i for i in builtins_list}
