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


# ### Instructions
Instruction = namedtuple('Instruction', ['name', 'opcode', 'fn'])


def inst_cup(machine):
    '''Call user procedure'''
    raise NotImplementedError


def inst_csp(machine):
    '''Call standard procedure'''
    raise NotImplementedError


def inst_ent(machine):
    '''Procedure entry'''
    raise NotImplementedError


def inst_mst(machine):
    '''Mark stack'''
    raise NotImplementedError


def inst_rtn(machine):
    '''Return'''
    raise NotImplementedError


def inst_equ(machine):
    '''Equality comparison'''
    raise NotImplementedError


def inst_neq(machine):
    '''Inequality comparison'''
    raise NotImplementedError


def inst_grt(machine):
    '''Greater than comparison'''
    raise NotImplementedError


def inst_geq(machine):
    '''Greater than or equal comparison'''
    raise NotImplementedError


def inst_les(machine):
    '''Less than comparison'''
    raise NotImplementedError


def inst_leq(machine):
    '''Less than or equal comparison'''
    raise NotImplementedError


def inst_adi(machine):
    '''Integer addition'''
    raise NotImplementedError


def inst_sbi(machine):
    '''Integer subtraction'''
    raise NotImplementedError


def inst_ngi(machine):
    '''Integer sign inversion'''
    raise NotImplementedError


def inst_mpi(machine):
    '''Integer multiplication'''
    raise NotImplementedError


def inst_dvi(machine):
    '''Integer divison'''
    raise NotImplementedError


def inst_mod(machine):
    '''Integer modulo'''
    raise NotImplementedError


def inst_abi(machine):
    '''Integer absolute value'''
    raise NotImplementedError


def inst_sqi(machine):
    '''Integer square'''
    raise NotImplementedError


def inst_inc(machine):
    '''Increment'''
    raise NotImplementedError


def inst_dec(machine):
    '''Decrement'''
    raise NotImplementedError


def inst_adr(machine):
    '''Real addition'''
    raise NotImplementedError


def inst_sbr(machine):
    '''Real subtraction'''
    raise NotImplementedError


def inst_ngr(machine):
    '''Real sign inversion'''
    raise NotImplementedError


def inst_mpr(machine):
    '''Real multiplication'''
    raise NotImplementedError


def inst_dvr(machine):
    '''Real divison'''
    raise NotImplementedError


def inst_abr(machine):
    '''Real absolute value'''
    raise NotImplementedError


def inst_sqr(machine):
    '''Real square'''
    raise NotImplementedError


def inst_ior(machine):
    '''Inclusive OR'''
    raise NotImplementedError


def inst_and(machine):
    '''And'''
    raise NotImplementedError


def inst_xor(machine):
    '''Exclusive OR'''
    raise NotImplementedError


def inst_not(machine):
    '''Complement'''
    raise NotImplementedError


def inst_inn(machine):
    '''Set membership'''
    raise NotImplementedError


def inst_uni(machine):
    '''Set union'''
    raise NotImplementedError


def inst_int(machine):
    '''Set intersection'''
    raise NotImplementedError


def inst_dif(machine):
    '''Set difference'''
    raise NotImplementedError


def inst_cmp(machine):
    '''Set complement'''
    raise NotImplementedError


def inst_sgs(machine):
    '''Generate singleton set'''
    raise NotImplementedError


def inst_ujp(machine):
    '''Unconditional jump'''
    raise NotImplementedError


def inst_xjp(machine):
    '''Indexed jump'''
    raise NotImplementedError


def inst_fjp(machine):
    '''False jump'''
    raise NotImplementedError


def inst_tjp(machine):
    '''True jump'''
    raise NotImplementedError


def inst_flt(machine):
    '''Float top of stack'''
    raise NotImplementedError


def inst_flo(machine):
    '''Float next to top of stack'''
    raise NotImplementedError


def inst_trc(machine):
    '''Truncate'''
    raise NotImplementedError


def inst_md(machine):
    '''Round'''
    raise NotImplementedError


def inst_chr(machine):
    '''Convert to character'''
    raise NotImplementedError


def inst_ord(machine):
    '''Convert to integer'''
    raise NotImplementedError


def inst_stp(machine):
    '''Stop machine.'''
    machine.stop_machine()


def inst_lda(machine):
    '''Load address of data'''
    raise NotImplementedError


def inst_ldc(machine):
    '''Load constant'''
    raise NotImplementedError


def inst_ldi(machine):
    '''Load indirect'''
    raise NotImplementedError


def inst_lva(machine):
    '''Load value (address)'''
    raise NotImplementedError


def inst_lvb(machine):
    '''Load value (boolean)'''
    raise NotImplementedError


def inst_lvc(machine):
    '''Load value (character)'''
    raise NotImplementedError


def inst_lvi(machine):
    '''Load value (integer)'''
    raise NotImplementedError


def inst_lvr(machine):
    '''Load value (real)'''
    raise NotImplementedError


def inst_lvs(machine):
    '''Load value (set)'''
    raise NotImplementedError


def inst_sti(machine):
    '''Store indirect'''
    raise NotImplementedError


def inst_ixa(machine):
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
instructions = {i.opcode: i for i in insts_list}


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
builtin_default_fn = lambda *args, **kwargs: panic(NotImplementedError)

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

        self._stack[index] = something

    def low_get_at(self, index):
        '''Retrieve an element in the lowend stack with given index.
        If the index is illegal, raises `IndexError`.

        :param index: specify index.
        '''
        if index >= self._low_top or index < self._low_bottom:
            raise IndexError('Invalid position.')

        return self._stack[index]

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

        self._stack[index] = something

    def high_get_at(self, index):
        '''Retrieve an element in the highend stack with given index.
        If the index is illegal, raises `IndexError`.

        :param index: specify index.
        '''
        if index <= self._high_top or index > self._high_bottom:
            raise IndexError('Invalid position.')

        return self._stack[index]

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

    # Supported instrucitons map.
    instructions = instructions

    def __init__(self, stdin, stdout):
        self.stdin = stdin
        self.stdout = stdout

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

        # Machine state.
        self.state = self.STATE_STOP

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

    def advance_pc(self):
        '''Move pc forward an instruction.'''
        self.pc = self.pc + 1

    @property
    def is_machine_running(self):
        return self.state == self.STATE_RUNNING

    def start_machine(self):
        '''Start the machine.'''
        self.state = self.STATE_RUNNING

    def stop_machine(self):
        '''Stop the machine.'''
        self.state = self.STATE_STOP

    def execute(self, instructions, start_pc):
        '''Execute instructions.

        :param instructions: instructions to be executed.
        :param start_pc: instructions entry point.
        '''
        self.reset(instructions, start_pc)

        self.start_machine()

        while self.is_machine_running:
            try:
                self.execute_instruction()
            except Exception as e:
                self.stop_machine()
                raise e

    def execute_instruction(self):
        '''Execute an instruction.'''
        inst_bytecode = self.istore[self.pc]
        self.advance_pc()

        op, op1, op2 = disassemble_instruction(inst_bytecode)
        inst = self.instructions.get(op, None)
        if not inst:
            panic(message='Unknown instruction: {0:#032b}'.format(
                inst_bytecode
            ))

        inst.fn(self)

    def reset(self, instructions, start_pc):
        '''Reset machine state.

        TODO prepare constants area.
        :param instructions: instructions to be executed.
        :param start_pc: instructions entry point.
        '''
        self.istore = instructions
        self.dstore.reset()
        self.pc = start_pc
        self.ep = 0
        self.mp = 0
        self.np_bottom = 0
        self.state = self.STATE_STOP

    def stack_push(self, data):
        '''Push data to stack.

        :param data: data to be pushed into the stack.
        '''
        self.dstore.push_high(data)

    def stack_pop(self):
        '''Pop from stack.'''
        return self.dstore.pop_high()

    def malloc(self, size):
        raise NotImplementedError

    def free(self, address):
        raise NotImplementedError


if __name__ == '__main__':
    machine = Machine(None, None)
    machine.execute([0x30, 0x10], 0)    # Should stop the machine.
