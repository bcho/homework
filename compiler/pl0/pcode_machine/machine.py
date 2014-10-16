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

    def execute(self, instructions, start_pc):
        '''Execute instructions.

        :param instructions: instructions to be executed.
        :param start_pc: instructions entry point.
        '''
        self.reset(instructions, start_pc)

    def reset(self, instructions, start_pc):
        '''Reset machine state.

        TODO prepare constants area.
        :param instructions: instructions to be executed.
        :param start_pc: instructions entry point.
        '''
        self.istore = instructions
        self.pc = start_pc
        self.ep = 0
        self.mp = 0
        self.np = 0
        self.np_bottom = 0
        self.sp = 0

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
