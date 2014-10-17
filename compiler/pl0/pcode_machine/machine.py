# coding: utf-8

'''
# P-Code Machine

### Reference:

- http://cs2.uco.edu/~trt/cs4173/pspec.pdf
- https://github.com/lkesteloot/turbopascal
'''

import math
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
OPCODE_SHIFT = 0
OP1_BITS = 8
OP1_SHIFT = OPCODE_SHIFT + OPCODE_BITS
OP2_BTIS = 16
OP2_SHIFT = OP1_SHIFT + OP1_BITS

OPCODE_MASK = (1 << OPCODE_BITS) - 1
GET_OPCODE = lambda x: (int(x) >> OPCODE_SHIFT) & OPCODE_MASK
OP1_MASK = (1 << OP1_BITS) - 1
GET_OP1 = lambda x: (int(x) >> OP1_SHIFT) & OP1_MASK
OP2_MASK = (1 << OP2_BTIS) - 1
GET_OP2 = lambda x: (int(x) >> OP2_SHIFT) & OP2_MASK


def disassemble_instruction(inst):
    '''Disassemble an instruction, returns (opcode, op1, op2).

    :param inst: instruction to be disassembled.
    '''
    return (GET_OPCODE(inst), GET_OP1(inst), GET_OP2(inst))


def assemble_instruction(opcode, op1=None, op2=None):
    '''Assemble an instruction.

    :param opcode: opcode or opcode name.
    :param op1: operand 1.
    :param op2: operand 2.
    '''
    if op1 is None:
        op1 = 0
    if op2 is None:
        op2 = 0
    if isinstance(opcode, str):
        opcode = INSTRUCTION_NAMES[opcode].opcode

    opcode, op1, op2 = int(opcode), int(op1), int(op2)
    return op2 << OP2_SHIFT | op1 << OP1_SHIFT | opcode << OPCODE_SHIFT


# ### Instructions
Instruction = namedtuple('Instruction', ['name', 'opcode', 'fn'])


def inst_cup(op1, op2, machine):
    '''Call user procedure'''
    raise NotImplementedError


def inst_csp(op1, op2, machine):
    '''Call standard procedure'''
    raise NotImplementedError


def inst_ent(op1, op2, machine):
    '''Procedure entry'''
    raise NotImplementedError


def inst_mst(op1, op2, machine):
    '''Mark stack'''
    raise NotImplementedError


def inst_rtn(op1, op2, machine):
    '''Return'''
    raise NotImplementedError


def inst_equ(op1, op2, machine):
    '''Equality comparison'''
    op_type = get_type_name_from_value(op1)
    x1, x2 = machine.stack_pop(), machine.stack_pop()
    machine.stack_push(take_as(x1, op_type) == take_as(x2, op_type))


def inst_neq(op1, op2, machine):
    '''Inequality comparison'''
    op_type = get_type_name_from_value(op1)
    x1, x2 = machine.stack_pop(), machine.stack_pop()
    machine.stack_push(take_as(x1, op_type) != take_as(x2, op_type))


def inst_grt(op1, op2, machine):
    '''Greater than comparison'''
    op_type = get_type_name_from_value(op1)
    x1, x2 = machine.stack_pop(), machine.stack_pop()
    machine.stack_push(take_as(x1, op_type) > take_as(x2, op_type))


def inst_geq(op1, op2, machine):
    '''Greater than or equal comparison'''
    op_type = get_type_name_from_value(op1)
    x1, x2 = machine.stack_pop(), machine.stack_pop()
    machine.stack_push(take_as(x1, op_type) <= take_as(x2, op_type))


def inst_les(op1, op2, machine):
    '''Less than comparison'''
    op_type = get_type_name_from_value(op1)
    x1, x2 = machine.stack_pop(), machine.stack_pop()
    machine.stack_push(take_as(x1, op_type) < take_as(x2, op_type))


def inst_leq(op1, op2, machine):
    '''Less than or equal comparison'''
    op_type = get_type_name_from_value(op1)
    x1, x2 = machine.stack_pop(), machine.stack_pop()
    machine.stack_push(take_as(x1, op_type) <= take_as(x2, op_type))


def inst_adi(op1, op2, machine):
    '''Integer addition'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'i') + take_as(i1, 'i')
    machine.stack_push(i3)


def inst_sbi(op1, op2, machine):
    '''Integer subtraction'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'i') - take_as(i1, 'i')
    machine.stack_push(i3)


def inst_ngi(op1, op2, machine):
    '''Integer sign inversion'''
    i1 = machine.stack_pop()
    i2 = - take_as(i1, 'i')
    machine.stack_push(i2)


def inst_mpi(op1, op2, machine):
    '''Integer multiplication'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'i') * take_as(i1, 'i')
    machine.stack_push(i3)


def inst_dvi(op1, op2, machine):
    '''Integer divison'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'i') // take_as(i1, 'i')
    machine.stack_push(i3)


def inst_mod(op1, op2, machine):
    '''Integer modulo'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'i') % take_as(i1, 'i')
    machine.stack_push(i3)


def inst_abi(op1, op2, machine):
    '''Integer absolute value'''
    i1 = machine.stack_pop()
    i2 = abs(take_as(i1, 'i'))
    machine.stack_push(i2)


def inst_sqi(op1, op2, machine):
    '''Integer square'''
    i1 = machine.stack_pop()
    i2 = take_as(i1, 'i') ** 2
    machine.stack_push(i2)


def inst_inc(op1, op2, machine):
    '''Increment'''
    op_type = get_type_name_from_value(op1)
    if op_type not in ['a', 'b', 'c', 'i']:
        panic('Unsupported integral type: {0}'.format(op_type))

    i1 = take_as(machine.stack_pop(), op_type)

    if op_type == 'c':
        i2 = chr(ord(i1) + 1)
    else:
        i2 = i1 + 1

    machine.stack_push(i2)


def inst_dec(op1, op2, machine):
    '''Decrement'''
    op_type = get_type_name_from_value(op1)
    if op_type not in ['a', 'b', 'c', 'i']:
        panic('Unsupported integral type: {0}'.format(op_type))

    i1 = take_as(machine.stack_pop(), op_type)

    if op_type == 'c':
        i2 = chr(ord(i1) - 1)
    else:
        i2 = i1 - 1

    machine.stack_push(i2)


def inst_adr(op1, op2, machine):
    '''Real addition'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'r') + take_as(i1, 'r')
    machine.stack_push(i3)


def inst_sbr(op1, op2, machine):
    '''Real subtraction'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'r') - take_as(i1, 'r')
    machine.stack_push(i3)


def inst_ngr(op1, op2, machine):
    '''Real sign inversion'''
    i1 = machine.stack_pop()
    i2 = - take_as(i1, 'r')
    machine.stack_push(i2)


def inst_mpr(op1, op2, machine):
    '''Real multiplication'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'r') * take_as(i1, 'r')
    machine.stack_push(i3)


def inst_dvr(op1, op2, machine):
    '''Real divison'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'r') / take_as(i1, 'r')
    machine.stack_push(i3)


def inst_abr(op1, op2, machine):
    '''Real absolute value'''
    i1 = machine.stack_pop()
    i2 = abs(take_as(i1, 'r'))
    machine.stack_push(i2)


def inst_sqr(op1, op2, machine):
    '''Real square'''
    i1 = machine.stack_pop()
    i2 = take_as(i1, 'r') ** 2
    machine.stack_push(i2)


def inst_ior(op1, op2, machine):
    '''Inclusive OR'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'r') or take_as(i1, 'r')
    machine.stack_push(i3)


def inst_and(op1, op2, machine):
    '''And'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'r') and take_as(i1, 'r')
    machine.stack_push(i3)


def inst_xor(op1, op2, machine):
    '''Exclusive OR'''
    i1, i2 = machine.stack_pop(), machine.stack_pop()
    i3 = take_as(i2, 'r') ^ take_as(i1, 'r')
    machine.stack_push(i3)


def inst_not(op1, op2, machine):
    '''Complement'''
    i1 = machine.stack_pop()
    i2 = not take_as(i1, 'r')
    machine.stack_push(i2)


def inst_inn(op1, op2, machine):
    '''Set membership'''
    raise NotImplementedError


def inst_uni(op1, op2, machine):
    '''Set union'''
    raise NotImplementedError


def inst_int(op1, op2, machine):
    '''Set intersection'''
    raise NotImplementedError


def inst_dif(op1, op2, machine):
    '''Set difference'''
    raise NotImplementedError


def inst_cmp(op1, op2, machine):
    '''Set complement'''
    raise NotImplementedError


def inst_sgs(op1, op2, machine):
    '''Generate singleton set'''
    raise NotImplementedError


def inst_ujp(op1, op2, machine):
    '''Unconditional jump'''
    address = take_as(op2, 'a')
    machine.update_pc(address)


def inst_xjp(op1, op2, machine):
    '''Indexed jump'''
    base_address = take_as(op2, 'a')
    offset = take_as(machine.stack_pop(), 'i')
    machine.update_pc(base_address + offset)


def inst_fjp(op1, op2, machine):
    '''False jump'''
    address = take_as(op2, 'a')
    cond = take_as(machine.stack_pop(), 'b')
    if not cond:
        machine.update_pc(address)


def inst_tjp(op1, op2, machine):
    '''True jump'''
    address = take_as(op2, 'a')
    cond = take_as(machine.stack_pop(), 'b')
    if cond:
        machine.update_pc(address)


def inst_flt(op1, op2, machine):
    '''Float top of stack'''
    top = take_as(machine.stack_pop(), 'r')
    machine.stack_push(take_as(top, 'r'))


def inst_flo(op1, op2, machine):
    '''Float next to top of stack'''
    top = machine.stack_pop()
    next_to_top = take_as(machine.stack_pop(), 'i')
    machine.stack_push(take_as(next_to_top, 'r'))
    machine.stack_push(top)


def inst_trc(op1, op2, machine):
    '''Truncate'''
    top = take_as(machine.stack_pop(), 'r')
    # In python, `int(float_value)` will truncate the decimal
    machine.stack_push(take_as(top, 'i'))


def inst_md(op1, op2, machine):
    '''Round'''
    top = take_as(machine.stack_pop(), 'r')
    machine.stack_push(round(top))


def inst_chr(op1, op2, machine):
    '''Convert to character'''
    top = take_as(machine.stack_pop(), 'i')
    machine.stack_push(take_as(top, 'c'))


def inst_ord(op1, op2, machine):
    '''Convert to integer'''
    top = take_as(machine.stack_pop(), 'c')
    machine.stack_push(take_as(top, 'i'))


def inst_stp(op1, op2, machine):
    '''Stop machine.'''
    machine.stop_machine()


def inst_lda(op1, op2, machine):
    '''Load address of data'''
    raise NotImplementedError


def inst_ldc(op1, op2, machine):
    '''Load constant'''
    constant_type = get_type_name_from_value(op1)
    cindex = take_as(op2, 'i')
    constant = take_as(machine.constants_get_at(cindex), constant_type)
    machine.stack_push(constant)


def inst_ldi(op1, op2, machine):
    '''Load indirect'''
    raise NotImplementedError


def inst_lva(op1, op2, machine):
    '''Load value (address)'''
    raise NotImplementedError


def inst_lvb(op1, op2, machine):
    '''Load value (boolean)'''
    raise NotImplementedError


def inst_lvc(op1, op2, machine):
    '''Load value (character)'''
    raise NotImplementedError


def inst_lvi(op1, op2, machine):
    '''Load value (integer)'''
    raise NotImplementedError


def inst_lvr(op1, op2, machine):
    '''Load value (real)'''
    raise NotImplementedError


def inst_lvs(op1, op2, machine):
    '''Load value (set)'''
    raise NotImplementedError


def inst_sti(op1, op2, machine):
    '''Store indirect'''
    raise NotImplementedError


def inst_ixa(op1, op2, machine):
    '''Compute indexed address'''
    raise NotImplementedError


insts_list = [
    # Subprogram linkage ops.
    Instruction('CUP', 0x00, inst_cup),
    Instruction('CSP', 0x01, inst_csp),
    Instruction('ENT', 0x02, inst_ent),
    Instruction('MST', 0x03, inst_mst),
    Instruction('RTN', 0x04, inst_rtn),

    # Comparaion ops.
    Instruction('EQU', 0x05, inst_equ),
    Instruction('NEQ', 0x06, inst_neq),
    Instruction('GRT', 0x07, inst_grt),
    Instruction('GEQ', 0x08, inst_geq),
    Instruction('LES', 0x09, inst_les),
    Instruction('LEQ', 0x0A, inst_leq),

    # Arithmetic ops.
    Instruction('ADI', 0x0B, inst_adi),
    Instruction('SBI', 0x0C, inst_sbi),
    Instruction('NGI', 0x0D, inst_ngi),
    Instruction('MPI', 0x0E, inst_mpi),
    Instruction('DVI', 0x0F, inst_dvi),
    Instruction('MOD', 0x10, inst_mod),
    Instruction('ABI', 0x11, inst_abi),
    Instruction('SQI', 0x12, inst_sqi),
    Instruction('INC', 0x13, inst_inc),
    Instruction('DEC', 0x14, inst_dec),
    Instruction('ADR', 0x15, inst_adr),
    Instruction('SBR', 0x16, inst_sbr),
    Instruction('NGR', 0x17, inst_ngr),
    Instruction('MPR', 0x18, inst_mpr),
    Instruction('DVR', 0x19, inst_dvr),
    Instruction('ABR', 0x1A, inst_abr),
    Instruction('SQR', 0x1B, inst_sqr),

    # Boolean ops.
    Instruction('IOR', 0x1C, inst_ior),
    Instruction('AND', 0x1D, inst_and),
    Instruction('XOR', 0x1E, inst_xor),
    Instruction('NOT', 0x1F, inst_not),

    # Set ops. (Not implement yet.)
    Instruction('INN', 0x20, inst_inn),
    Instruction('UNI', 0x21, inst_uni),
    Instruction('INT', 0x22, inst_int),
    Instruction('DIF', 0x23, inst_dif),
    Instruction('CMP', 0x24, inst_cmp),
    Instruction('SGS', 0x25, inst_sgs),

    # Jump ops.
    Instruction('UJP', 0x26, inst_ujp),
    Instruction('XJP', 0x27, inst_xjp),
    Instruction('FJP', 0x28, inst_fjp),
    Instruction('TJP', 0x29, inst_tjp),

    # Conversion ops.
    Instruction('FLT', 0x2A, inst_flt),
    Instruction('FLO', 0x2B, inst_flo),
    Instruction('TRC', 0x2C, inst_trc),
    Instruction('MD',  0x2D, inst_md),
    Instruction('CHR', 0x2E, inst_chr),
    Instruction('ORD', 0x2F, inst_ord),

    # Program termination ops.
    Instruction('STP', 0x30, inst_stp),

    # Data reference ops.
    Instruction('LDA', 0x31, inst_lda),
    Instruction('LDC', 0x32, inst_ldc),
    Instruction('LDI', 0x33, inst_ldi),
    Instruction('LVA', 0x34, inst_lva),
    Instruction('LVB', 0x35, inst_lvb),
    Instruction('LVC', 0x36, inst_lvc),
    Instruction('LVI', 0x37, inst_lvi),
    Instruction('LVR', 0x38, inst_lvr),
    Instruction('LVS', 0x39, inst_lvs),
    Instruction('STI', 0x3A, inst_sti),
    Instruction('IXA', 0x3B, inst_ixa)
]

# Instruction opcode-ed map
INSTRUCTIONS = {i.opcode: i for i in insts_list}
# Instruction name-ed map
INSTRUCTION_NAMES = {i.name: i for i in insts_list}


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
REGISTERS = {i.name: i for i in registers_list}


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
DATA_TYPES = {i.type: i for i in data_types_list}
# Datatypes value-ed map
DATA_TYPE_VALUES = {i.value: i for i in data_types_list}


def take_as(data, type):
    '''Convert data with type.

    :param data: data to be converted.
    :param type: target type.
    '''
    data_type = DATA_TYPES[type]
    return data_type.converter(data)


def get_type_name_from_value(value):
    '''Get data type name from value.

    :param value: bytecode type value.
    '''
    return DATA_TYPE_VALUES[value].type


def get_type_value_from_name(name):
    '''Get data type value from name.

    :parma name: data type name.
    '''
    return DATA_TYPES[name].value


# ## Builtin Functions.

Builtin = namedtuple('Builtin', ['name', 'opcode', 'fn'])


def builtin_rdb(machine):
    '''Read boolean.'''
    address = take_as(machine.stack_pop(), 'a')
    # Won't use provided file obj here.
    machine.stack_pop()

    raw_value = machine.stdin.read(1)
    # Only `0` will be `false` value.
    if raw_value == '0':
        value = False
    else:
        value = True

    machine.write_at(address, value)


def builtin_rdc(machine):
    '''Read char.'''
    address = take_as(machine.stack_pop(), 'a')
    # Won't use provided file obj here.
    machine.stack_pop()

    value = machine.stdin.read(1)
    machine.write_at(address, value)


def builtin_rdi(machine):
    '''Read integer.'''
    address = take_as(machine.stack_pop(), 'a')
    # Won't use provided file obj here.
    machine.stack_pop()

    raw_value = machine.stdin.readline()
    value = take_as(raw_value.strip(), 'i')
    machine.write_at(address, value)


def builtin_rdr(machine):
    '''Read real.'''
    address = take_as(machine.stack_pop(), 'a')
    # Won't use provided file obj here.
    machine.stack_pop()

    raw_value = machine.stdin.readline()
    value = take_as(raw_value.strip(), 'r')
    machine.write_at(address, value)


def builtin_rln(machine):
    '''Read `\n`.'''
    # Won't use provided file obj here.
    machine.stack_pop()

    # Read until `\n`.
    machine.stdin.readline()


def builtin_wrb(machine):
    '''Write boolean.'''
    width = take_as(machine.stack_pop(), 'i')
    value = str(take_as(machine.stack_pop(), 'b'))
    # Won't use provided file obj here.
    machine.stack_pop()

    right_justified_spaces = max(0, width - len(value))
    output = (' ' * right_justified_spaces) + value
    machine.stdout.write(output)


def builtin_wrc(machine):
    '''Write char.'''
    width = take_as(machine.stack_pop(), 'i')
    value = str(take_as(machine.stack_pop(), 'c'))
    # Won't use provided file obj here.
    machine.stack_pop()

    right_justified_spaces = max(0, width - len(value))
    output = (' ' * right_justified_spaces) + value
    machine.stdout.write(output)


def builtin_wri(machine):
    '''Write integer.'''
    width = take_as(machine.stack_pop(), 'i')
    value = str(take_as(machine.stack_pop(), 'i'))
    # Won't use provided file obj here.
    machine.stack_pop()

    right_justified_spaces = max(0, width - len(value))
    output = (' ' * right_justified_spaces) + value
    machine.stdout.write(output)


def builtin_wre(machine):
    '''Write real, exponential format.'''
    fraction_width = take_as(machine.stack_pop(), 'i')
    width = take_as(machine.stack_pop(), 'i')
    value = str(take_as(machine.stack_pop(), 'i'))
    # Won't use provided file obj here.
    machine.stack_pop()

    exp = '{0:.{1}e}'.format(value, fraction_width)
    right_justified_spaces = max(0, width - len(exp))
    output = (' ' * right_justified_spaces) + exp
    machine.stdout.write(output)


def builtin_wrf(machine):
    '''Write real, fixed format.'''
    fraction_width = take_as(machine.stack_pop(), 'i')
    width = take_as(machine.stack_pop(), 'i')
    value = str(take_as(machine.stack_pop(), 'i'))
    # Won't use provided file obj here.
    machine.stack_pop()

    exp = '{0:.{1}f}'.format(value, fraction_width)
    right_justified_spaces = max(0, width - len(exp))
    output = (' ' * right_justified_spaces) + exp
    machine.stdout.write(output)


def builtin_wrs(machine):
    '''Write string.'''
    address = take_as(machine.stack_pop(), 'a')
    # Won't use provided file obj here.
    machine.stack_pop()

    machine.stdout.write(take_as(machine.get_at(address), 's'))


def builtin_wln(machine):
    '''Write `\n`.'''
    # Won't use provided file obj here.
    machine.stack_pop()

    machine.stdout.write('\n')


def builtin_sqt(machine):
    '''Squre root.'''
    value = take_as(machine.stack_pop(), 'r')
    machine.stack_push(math.sqrt(value))


def builtin_ln(machine):
    '''Natural logarithm.'''
    value = take_as(machine.stack_pop(), 'r')
    machine.stack_push(math.log(value))


def builtin_exp(machine):
    '''Exponentiation.'''
    value = take_as(machine.stack_pop(), 'r')
    machine.stack_push(math.exp(value))


builtins_list = [
    Builtin('rdb', 0x00, builtin_rdb),
    Builtin('rdc', 0x01, builtin_rdc),
    Builtin('rdi', 0x02, builtin_rdi),
    Builtin('rdr', 0x03, builtin_rdr),
    Builtin('rln', 0x04, builtin_rln),
    Builtin('wrb', 0x05, builtin_wrb),
    Builtin('wrc', 0x06, builtin_wrc),
    Builtin('wri', 0x07, builtin_wri),
    Builtin('wre', 0x08, builtin_wre),
    Builtin('wrf', 0x09, builtin_wrf),
    Builtin('wrs', 0x0A, builtin_wrs),
    Builtin('wln', 0x0B, builtin_wln),
    Builtin('sqt', 0x0C, builtin_sqt),
    Builtin('ln',  0x0D, builtin_ln),
    Builtin('exp', 0x0E, builtin_exp)
]

builtins = {i.name: i for i in builtins_list}


# ## Machine


class DoubleEndStack(object):
    '''Double end stack with capacity.

    :param capacity: stack's capacity.
    '''

    INITIAL_VALUE = 0

    def __init__(self, capacity):
        # Stack capacity.
        self.capacity = capacity
        assert(self.capacity > 0), 'Should have positive capacity.'

        # Stack instance.
        self._stack = []

        # Lowend stack top, points to next available cell, starts from 0.
        self._low_top = 0

        # Lowend stack bottom, points to 0.
        self._low_bottom = 0

        # Highend stack top, points to next available cell,
        # starts from `capacity` - 1.
        self._high_top = self.capacity - 1

        # Highend stack bottom, points to `capacity` - 1.
        self._high_bottom = self.capacity - 1

        self.reset()

    def reset(self):
        '''Reset stack.'''
        self._stack = [self.INITIAL_VALUE for i in range(self.capacity)]

        self._low_top = 0
        self._high_top = self.capacity - 1

    @property
    def is_low_empty(self):
        '''Indicates if the lowend stack is empty.'''
        return self._low_top <= self._low_bottom

    @property
    def is_low_full(self):
        '''Indicates if the lowend stack is full.'''
        return self._low_top > self._high_top

    def push_low(self, something):
        '''Push something into the lowend stack,
        raises an `IndexError` when overflow.

        :param something: anything you want to push into the stack.
        '''
        if self.is_low_full:
            raise IndexError('Stack overflow.')

        self._stack[self._low_top] = something
        self._low_top = self._low_top + 1

    def pop_low(self):
        '''Pop an element from lowend stack,
        raises `IndexError` when stack is empty.'''
        if self.is_low_empty:
            raise IndexError('Empty stack.')

        self._low_top = self._low_top - 1
        element = self._stack[self._low_top]

        return element

    def low_push_at(self, index, something):
        '''Push something in the lowend stack with given index.
        If the index is illegal, raises `IndexError`.

        :param index: index to be written.
        :param something: anything you want to push into the stack.
        '''
        if index >= self._low_top or index < self._low_bottom:
            raise IndexError('Invalid position.')

        self.push_at(index, something)

    def low_get_at(self, index):
        '''Retrieve an element in the lowend stack with given index.
        If the index is illegal, raises `IndexError`.

        :param index: specify index.
        '''
        if index >= self._low_top or index < self._low_bottom:
            raise IndexError('Invalid index.')

        return self.get_at(index)

    def low_move_to(self, index, fill_value):
        '''Move low index to a new index.
        If the stack needs to expand, fill the new cells with `fill_value`.
        Raise `IndexError` if the new index is illegal.

        :param index: new index.
        :param fill_value: filled value for new cells.
        '''
        if index > self._high_top:
            raise IndexError('Stack overflow.')
        if index < self._low_bottom:
            raise IndexError('Stack underflow.')

        while index >= self._low_top:
            self.push_low(fill_value)
        while index < self._low_top - 1:
            self.pop_low()

    @property
    def low_top(self):
        '''Get lowend stack's top element.
        Returns `None` when the lowend stack is empty.
        '''
        if self.is_low_empty:
            return None
        return self._stack[self._low_top - 1]

    @property
    def low_top_index(self):
        '''Get lowend stack's top index.'''
        return self._low_top - 1

    @property
    def is_high_empty(self):
        '''Indicates if the highend stack is empty.'''
        return self._high_top >= self._high_bottom

    @property
    def is_high_full(self):
        '''Indicates if the highend stack is full.'''
        return self._high_top < self._low_top

    def push_high(self, something):
        '''Push something into the highend stack,
        raises an `IndexError` when overflow.

        :param something: anything you want to push into the stack.
        '''
        if self.is_high_full:
            raise IndexError('Stack overflow.')

        self._stack[self._high_top] = something
        self._high_top = self._high_top - 1

    def pop_high(self):
        '''Pop an element from lowend stack,
        raises `IndexError` when stack is empty.'''
        if self.is_high_empty:
            raise IndexError('Empty stack.')

        self._high_top = self._high_top + 1
        element = self._stack[self._high_top]

        return element

    def high_push_at(self, index, something):
        '''Push something in the highend stack with given index.
        If the index is illegal, raises `IndexError`.

        :param index: index to be written.
        :param something: anything you want to push into the stack.
        '''
        if index <= self._high_top or index > self._high_bottom:
            raise IndexError('Invalid position.')

        self.push_at(index, something)

    def high_get_at(self, index):
        '''Retrieve an element in the highend stack with given index.
        If the index is illegal, raises `IndexError`.

        :param index: specify index.
        '''
        if index <= self._high_top or index > self._high_bottom:
            raise IndexError('Invalid index.')

        return self.get_at(index)

    def high_move_to(self, index, fill_value):
        '''Move high index to a new index.
        If the stack needs to expand, fill the new cells with `fill_value`.
        Raise `IndexError` if the new index is illegal.

        :param index: new index.
        :param fill_value: filled value for new cells.
        '''
        if index < self._low_top:
            raise IndexError('Stack overflow.')
        if index > self._high_bottom:
            raise IndexError('Stack underflow.')

        while index <= self._high_top:
            self.push_high(fill_value)
        while index > self._high_top + 1:
            self.pop_high()

    @property
    def high_top(self):
        '''Get highend stack's top element.
        Returns `None` when the highend stack is empty.
        '''
        if self.is_high_empty:
            return None
        return self._stack[self._high_top + 1]

    @property
    def high_top_index(self):
        '''Get highend stack's top index.'''
        return self._high_top + 1

    def push_at(self, index, something):
        '''Push something into the stack with given index.

        If the index is illegal, raises `IndexError`.

        :param index: index to be written.
        :param something: anything you want to push into the stack.
        '''
        if index < 0 or index >= self.capacity:
            raise IndexError('Invalid position.')

        self._stack[index] = something

    def get_at(self, index):
        '''Retrieve an element in the stack with given index.
        If the index is illegal, raises 'IndexError`.

        :param index: specify index.
        '''
        if index < 0 or index >= self.capacity:
            raise IndexError('Invalid index.')

        return self._stack[index]


class MachineBaseDebugger(object):
    '''Machine base debugger.'''

    def debug(self, machine):
        '''Debug a machine.

        :param machine: target machine.
        '''
        raise NotImplementedError

    def __call__(self, machine):
        self.debug(machine)


class MachineInspector(MachineBaseDebugger):
    '''Machine state inspector.'''

    # Stack inspect cells count.
    _stack_print_size = 10

    # Heap inspect cells count.
    _heap_print_size = 10

    _inspect_tmpl = '''
Registers

    PC: {pc:#032b}
    MP: {mp:#032b}
    NP: {mp:#032b}
    SP: {sp:#032b}

Statck

{stack}

Heap

{heap}

Current Instruction

{cur_inst}
'''

    _stack_inspect_tmpl = '\t{index}: {content}'
    _heap_inspect_tmpl = '\t{index}: {content}'
    _inst_inspect_tmpl = '\t{opcode} {op1:02x} {op2:04x}'

    def debug(self, machine):
        '''Print out machine inner states, includes:

        - pc / mp / np / sp value
        - stack content
        - heap content
        - current instruction

        :param machine: target machine
        '''
        facts = {
            'stack': self._debug_stack(machine),
            'heap': self._debug_heap(machine),
            'cur_inst': self._debug_instruction(machine.current_instruction)
        }
        facts.update(machine.registers)

        print(self._inspect_tmpl.format(**facts))

    def _debug_stack(self, machine, inspect_count=None):
        '''Inspect machine's stack.

        :param machine: target machine.
        :param inspect_count: inspect cells count.
                              Defaults to `_stack_print_size`.
        '''
        inspect_count = inspect_count or self._stack_print_size

        cells = []
        for sp in range(machine.sp, machine.sp + inspect_count):
            try:
                content = machine.dstore.high_get_at(sp)
            except IndexError:
                break
            cells.append(self._stack_inspect_tmpl.format(
                index=sp,
                content=content
            ))
        cells.reverse()
        return '\n'.join(cells)

    def _debug_heap(self, machine, inspect_count=None):
        '''Inspect machine's heap.

        :param machine: target machine.
        :param inspect_count: inspect cells count.
                              Defaults to `_heap_print_size`
        '''
        # TODO
        return '\t<unknown>'

    def _debug_instruction(self, instruction):
        '''Inspect an instruction.

        :param instruction: bytecode to be explained.
        '''
        opcode, op1, op2 = disassemble_instruction(instruction)
        opcode_name = INSTRUCTIONS[opcode].name
        return self._inst_inspect_tmpl.format(opcode=opcode_name,
                                              op1=op1,
                                              op2=op2)


class Machine(object):
    '''P-code machine implementation.

    TODO handle stdin / stdout
    :param stdin: machine's stdin environment.
    :param stdout: machine's stdout environment.
    '''

    # Data store capacity.
    DATA_STORE_CAPACITY = 65536

    # Stack frame size.
    #
    # ### Stack frame:
    #
    # MP (frame begin) ->   +------------+
    #                       |     RV     |
    #                       +------------+
    #                       |     SL     |
    #                       +------------+
    #                       |     DL     |
    #                       +------------+
    #                       |     EP     |
    #                       +------------+
    #                       |     RA     |
    # SP (maybe here)  ->   +------------+
    STACK_FRAME_SIZE = 5

    # Machine state constant.
    STATE_STOP = 0
    STATE_RUNNING = 1

    # Supported instructions map.
    SUPPORT_INSTRUCTIONS = INSTRUCTIONS

    def __init__(self, stdin, stdout, debugger=None):
        '''P-Machine

        :param stdin: machine running env's standard input file object.
        :param stdout: machine runnint env's standard output file object.
        :param debugger: machine debugger. Defaults to `None`.
        '''
        self.stdin = stdin
        self.stdout = stdout

        self.debugger = debugger

        # Instructions store.
        self.istore = None

        # Program counter.
        self.pc = 0

        # Data store.
        self.dstore = DoubleEndStack(self.DATA_STORE_CAPACITY)

        # Extreme pointer. (Won't be used here.)
        self.ep = 0

        # Mark pointer. See `stack frame` description above.
        self.mp = 0

        # New pointer bottom, points to the bottom of the heap.
        self.np_bottom = 0

        # Constants list.
        self.constants = []

        # Machine state.
        self.state = self.STATE_STOP

        # Machine current instruction.
        self.current_instruction = None

    @property
    def sp(self):
        '''Stack pointer, see `stack frame` description above.'''
        # Use the highend of dstore.
        return self.dstore.high_top_index

    @property
    def np(self):
        '''New pointer, points to the top of the heap.'''
        # Use the lowend of dstore.
        return self.dstore.low_top_index

    @property
    def registers(self):
        '''Current registers value.'''
        return {
            'pc': self.pc,
            'mp': self.mp,
            'np': self.np,
            'sp': self.sp
        }

    def update_pc(self, to=None):
        '''Move pc forward.

        :param to: target pc, defaults to current pc + 1.
        '''
        if to is None:
            to = self.pc + 1
        self.pc = to

    @property
    def is_machine_running(self):
        return self.state == self.STATE_RUNNING

    def start_machine(self):
        '''Start the machine.'''
        self.state = self.STATE_RUNNING

    def stop_machine(self):
        '''Stop the machine.'''
        self.state = self.STATE_STOP

    def execute(self, instructions, typed_constants, constants, start_pc):
        '''Execute instructions.

        :param instructions: instructions to be executed.
        :param typed_constants: pre-alloced constants, store in dstore.
        :param constants: integer / string contants.
        :param start_pc: instructions entry point.
        '''
        self.reset(instructions, typed_constants, constants, start_pc)

        self.start_machine()

        while self.is_machine_running:
            try:
                self.execute_instruction()
            except Exception as e:
                self.stop_machine()
                if self.debugger:
                    debugger(self)
                raise e

    def execute_instruction(self):
        '''Execute an instruction.'''
        self.current_instruction = inst_bytecode = self.istore[self.pc]
        self.update_pc()

        op, op1, op2 = disassemble_instruction(inst_bytecode)
        inst = self.SUPPORT_INSTRUCTIONS.get(op, None)
        if not inst:
            panic(message='Unknown instruction: {0:#032b}'.format(
                inst_bytecode
            ))

        inst.fn(op1, op2, self)

    def reset(self, instructions, typed_constants, constants, start_pc):
        '''Reset machine state.

        TODO prepare typed constants area.
        :param instructions: instructions to be executed.
        :param typed_constants: pre-alloced constants, stores in dstore.
        :param constants: integer / string constants.
        :param start_pc: instructions entry point.
        '''
        self.istore = instructions
        self.dstore.reset()
        self.pc = start_pc
        self.ep = 0
        self.mp = 0
        self.np_bottom = 0
        self.constants = constants
        self.state = self.STATE_STOP
        self.current_instruction = None

    def stack_push(self, data):
        '''Push data to stack.

        :param data: data to be pushed into the stack.
        '''
        self.dstore.push_high(data)

    def stack_pop(self):
        '''Pop from stack.'''
        return self.dstore.pop_high()

    def write_at(self, address, value):
        '''Write into arbitrary address in dstore.

        :param address: target address.
        :param value: value to be placed.
        '''
        self.dstore.push_at(address, value)

    def read_at(self, address):
        '''Read from dstore with arbitrary address.

        :param address: target address.
        '''
        self.dstore.get_at(address)

    def malloc(self, size):
        raise NotImplementedError

    def free(self, address):
        raise NotImplementedError

    def constants_get_at(self, index):
        '''Get a constant from bytecode constants.
        Raise `IndexError` if the index is invalid.

        :param index: constant index.
        '''
        return self.constants[index]


if __name__ == '__main__':
    debugger = MachineInspector()

    instructions = [
        assemble_instruction('LDC', get_type_value_from_name('i'), 0),
        assemble_instruction('LDC', get_type_value_from_name('i'), 1),
        assemble_instruction('LDC', get_type_value_from_name('i'), 1),
        assemble_instruction('LDC', get_type_value_from_name('s'), 2),
        assemble_instruction('LDC', get_type_value_from_name('i'), 1),
        assemble_instruction('LDC', get_type_value_from_name('r'), 1.1),
        assemble_instruction('EQU', get_type_value_from_name('i')),
        assemble_instruction('STP')
    ]
    machine = Machine(None, None, debugger)
    typed_constants = []
    constants = [1, 2, 'hello world']
    machine.execute(instructions, typed_constants, constants, 0)
    debugger(machine)
