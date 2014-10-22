# coding: utf-8

'''
# pl0 compiler

Compile [pl0][0] into p-machine bytecode.
'''

import sys
from functools import wraps
from enum import Enum


# ## Basic Routines

class CompileError(RuntimeError):
    '''General compile error.'''


# ## Token

class TokenType(Enum):
    # Status token
    EOF = (1, None)
    ERROR = (2, None)

    # Reserved keyword
    CONST = (3, 'const')
    VAR = (4, 'var')
    PROCEDURE = (5, 'procedure')
    BEGIN = (6, 'begin')
    END = (7, 'end')
    IF = (8, 'if')
    THEN = (9, 'then')
    WHILE = (10, 'while')
    DO = (11, 'do')
    ODD = (12, 'odd')
    CALL = (13, 'call')
    WRITE = (14, 'write')
    READ = (15, 'read')

    # Operator
    ASSIGN = (16, ':=')
    EQ = (17, '=')
    NEQ = (18, '#')
    LT = (19, '<')
    LEQ = (20, '<=')
    GT = (21, '>')
    GEQ = (22, '>=')
    LPAREN = (23, '(')
    RPAREN = (24, ')')
    COMMA = (25, ',')
    SEMI = (26, ';')
    PERIOD = (27, '.')
    PLUS = (28, '+')
    MINUS = (29, '-')
    TIMES = (30, '*')
    OVER = (31, '/')

    # Character
    IDENT = (32, None)
    NUM = (33, None)


RESERVED_KEYWORDS = {
    'const': TokenType.CONST,
    'var': TokenType.VAR,
    'procedure': TokenType.PROCEDURE,
    'begin': TokenType.BEGIN,
    'end': TokenType.END,
    'if': TokenType.IF,
    'then': TokenType.THEN,
    'while': TokenType.WHILE,
    'do': TokenType.DO,
    'odd': TokenType.ODD,
    'call': TokenType.CALL,
    'write': TokenType.WRITE,
    'read': TokenType.READ
}


class Token(object):
    '''Token instance.'''

    def __init__(self, type, lines, cols, value):
        # Token type, one of the `TokenType`.
        self.type = type

        # Token position in the source file.
        self.pos = dict(lines=lines, cols=cols)

        # Token value
        self.value = value

    def __str__(self):
        return '<Token: {type}:{value} at l{lines}:c{cols}>'.format(
            type=self.type,
            lines=self.pos['lines'],
            cols=self.pos['cols'],
            value=self.value or ''
        )


def _none_is_nonthing(func):
    @wraps(func)
    def wrapper(self, *args, **kwargs):
        if self.char is None:
            return False
        return func(self, *args, **kwargs)
    return wrapper


class TokenChar(object):
    '''Token character.

    :param char: internal character.
    :param iseof: indicates if it's a EOF. Defaults to `False`
    '''

    def __init__(self, char, iseof=None):
        if iseof is None:
            self._iseof = False
        else:
            self._iseof = iseof

        if char is not None and len(char) > 1:
            raise TypeError('Only accept single character.')
        self.char = char

    @_none_is_nonthing
    def isalpha(self):
        return self.char.isalpha()

    @_none_is_nonthing
    def isdigit(self):
        return self.char.isdigit()

    @_none_is_nonthing
    def isspace(self):
        return self.char.isspace()

    def iseof(self):
        return self._iseof

    @_none_is_nonthing
    def __eq__(self, other):
        return self.char == other

    def __add__(self, other):
        char = self.char or ''
        return other + char

    def __radd__(self, other):
        char = self.char or ''
        return other + char


class LexerState(Enum):

    START = 0
    IN_ASSIGNMENT = 1
    IN_COMMENT = 2
    IN_NUM = 3
    IN_IDENT = 4
    DONE = 5


class Lexer(object):
    '''Lexer.

    :param input_stream: file object, defaults to `stdin`.
    '''

    def __init__(self, input_stream=None):
        input_stream = input_stream or sys.stdin

        # Input stream.
        self._input_stream = input_stream

        # Current line buffer.
        self._line_buffer = ''

        # Current line no.
        self.lines = 0

        # Current column no.
        self.cols = 0

        # Peeked next token.
        self._next_token = None

    def reset(self):
        '''Reset lexer.'''
        self._line_buffer = ''
        self.lines, self.cols = 0, 0

    @property
    def tokens(self):
        '''Tokens stream.'''
        while True:
            token = self.get_token()
            if token.type == TokenType.EOF:
                raise StopIteration
            yield token

    def get_token(self):
        '''Get a token.'''
        token = self.peek()

        # Consume the next token.
        self._next_token = None

        return token

    def peek(self):
        '''Peek a token.'''
        if self._next_token is None:
            self._next_token = self._get_token()

        return self._next_token

    def _get_token(self):
        '''Get a token.'''
        cur_value, cur_token = '', None
        state = LexerState.START

        while state != LexerState.DONE:
            char = self._get_char()

            if state == LexerState.START:
                # Multi-characters states.
                if char.isdigit():
                    state = LexerState.IN_NUM
                    cur_value += char
                elif char.isalpha():
                    state = LexerState.IN_IDENT
                    cur_value += char
                elif char == ':':
                    state = LexerState.IN_ASSIGNMENT
                elif char.isspace():
                    pass  # Skip whitespaces.
                # Single character token.
                else:
                    state = LexerState.DONE
                    if char.iseof():
                        cur_token = self._make_token(TokenType.EOF)
                        break  # while state != LexerState.DONE
                    elif char == '+':
                        cur_token = self._make_token(TokenType.PLUS, '+')
                        break  # while state != LexerState.DONE
                    elif char == '-':
                        cur_token = self._make_token(TokenType.MINUS, '-')
                        break  # while state != LexerState.DONE
                    elif char == '*':
                        cur_token = self._make_token(TokenType.TIMES, '*')
                        break  # while state != LexerState.DONE
                    elif char == '/':
                        cur_token = self._make_token(TokenType.OVER, '/')
                        break  # while state != LexerState.DONE
                    elif char == '=':
                        cur_token = self._make_token(TokenType.EQ, '=')
                        break  # while state != LexerState.DONE
                    elif char == '#':
                        cur_token = self._make_token(TokenType.NEQ, '#')
                        break  # while state != LexerState.DONE
                    elif char == '<':
                        # peek for `=`
                        next_char = self._get_char()
                        if next_char == '=':
                            cur_token = self._make_token(TokenType.LEQ, '<=')
                        else:
                            cur_token = self._make_token(TokenType.LT, '<')
                            self._backup_char()
                        break  # while state != LexerState.DONE
                    elif char == '>':
                        # peek for `=`
                        next_char = self._get_char()
                        if next_char == '=':
                            cur_token = self._make_token(TokenType.GEQ, '>=')
                        else:
                            cur_token = self._make_token(TokenType.GT, '>')
                            self._backup_char()
                        break  # while state != LexerState.DONE
                    elif char == '(':
                        # peek for `*`:
                        next_char = self._get_char()
                        if next_char == '*':
                            state = LexerState.IN_COMMENT
                        else:
                            cur_token = self._make_token(TokenType.LPAREN, '(')
                            self._backup_char()
                            break  # while state != LexerState.DONE
                    elif char == ')':
                        cur_token = self._make_token(TokenType.RPAREN, ')')
                        break  # while state != LexerState.DONE
                    elif char == ',':
                        cur_token = self._make_token(TokenType.COMMA, ',')
                        break  # while state != LexerState.DONE
                    elif char == ';':
                        cur_token = self._make_token(TokenType.SEMI, ';')
                        break  # while state != LexerState.DONE
                    elif char == '.':
                        cur_token = self._make_token(TokenType.PERIOD)
                        break  # while state != LexerState.DONE
                    else:
                        cur_token = self._make_token(TokenType.ERROR)
                        break  # while state != LexerState.DONE

            elif state == LexerState.IN_ASSIGNMENT:
                state = LexerState.DONE
                if char == '=':
                    cur_token = self._make_token(TokenType.ASSIGN, ':=')
                else:
                    cur_token = self._make_token(
                        TokenType.ERROR,
                        'missing `=` for assignment'
                    )
                    # Restore from error.
                    self._backup_char()
                break  # while state != LexerState.DONE

            elif state == LexerState.IN_NUM:
                if char.isdigit():
                    cur_value += char
                else:
                    state = LexerState.DONE
                    cur_token = self._make_token(TokenType.NUM, int(cur_value))

                    # Restore state.
                    self._backup_char()

            elif state == LexerState.IN_IDENT:
                if char.isalpha() or char.isdigit():
                    cur_value += char
                else:
                    state = LexerState.DONE
                    # Test if it is a reserved keyword.
                    token_type = RESERVED_KEYWORDS.get(cur_value.lower(),
                                                       TokenType.IDENT)
                    cur_token = self._make_token(token_type, cur_value)

                    # Restore state.
                    self._backup_char()

            elif state == LexerState.IN_COMMENT:
                if char.iseof():
                    state = LexerState.DONE
                    cur_token = self._make_token(TokenType.ERROR,
                                                 'unexpected EOF, '
                                                 'maybe missing `*)`')
                elif char == '*':
                    next_char = self._get_char()
                    if next_char == ')':
                        state = LexerState.START
                    else:
                        # Skip over the comments.
                        pass

            else:
                raise CompileError('lexer: unexpected state.')

        return cur_token

    def _get_char(self):
        '''Get a token character from input stream.'''
        assert(self._input_stream is not None), 'Should setup input stream.'

        if self.cols >= len(self._line_buffer):
            self.lines += 1
            self.cols = 0
            self._line_buffer = self._input_stream.readline() + '\n'
            if self._line_buffer == '\n':
                char = TokenChar(None, True)
                return char

        char = self._line_buffer[self.cols]
        self.cols += 1

        return TokenChar(char)

    def _backup_char(self):
        '''Backup a character.'''
        # Statement in pl0 cannot cross line.
        self.cols -= 1

    def _make_token(self, token_type, value=None):
        '''Create a token.

        :param token_type: token's type.
        :param value: token's value, defaults to None
        '''
        cols = self.cols - 1
        if value is not None:
            cols = self.cols - len(str(value))
        return Token(token_type, self.lines, cols, value)

    def __iter__(self):
        return self.tokens

    def __next__(self):
        yield self.tokens


class ASTNode(object):
    '''Abstract syntaxt tree node.'''

    def __str__(self):
        return '<{0}>'.format(self.__class__.__name__)

    def __repr__(self):
        return self.__str__()


class BlockNode(ASTNode):
    '''Block node.

    :param constants: constants list.
    :param variables: variables list.
    :param procedures: procedures list.
    :param statement: statement.
    '''

    def __init__(self, constants, variables, procedures, statements):
        self.constants = constants
        self.variables = variables
        self.procedures = procedures
        self.statements = statements


class ProgramNode(ASTNode):
    '''PL/0 program node.

        const
            const1 = 2;
        var
            a, b, c;

        begin
            a := 1;
        end

    :param block: program body.
    '''

    def __init__(self, block):
        self.block = block


class ProcedureNode(ASTNode):
    '''Procedure node.

        procedure proc
        var
            local;
        begin
            READ(local);
        end

    TODO: need parent procedure ref?
    :param name: procedure identity name node.
    :param block: procedure body.
    '''

    def __init__(self, name, block):
        self.name = name
        self.block = block


class ConstNode(ASTNode):
    '''Constant declaration node. (value stored in symbol table.)

        const const1 = 2, const2 = 3;

    :param name: constant identity node.
    '''

    def __init__(self, name):
        self.name = name


class VarNode(ASTNode):
    '''Variable declaration node. (value stored in symbol table.)

        var a, b, c;

    :param name: constant identity node.
    '''

    def __init__(self, name):
        self.name = name


class CallUserProcedureNode(ASTNode):
    '''Call user defined procedure node.

        call proc1;

    :param procedure_name: called procedure identity node.
    '''

    def __init__(self, procedure_name):
        self.procedure_name = procedure_name


class CallBuiltinProcedureNode(ASTNode):
    '''Call builtin procedure node.

        write(42);

    :param builtin_name: called builtin identity node.
    :param parameters: called parameters list.
    '''

    def __init__(self, builtin_name, parameters):
        self.builtin_name = builtin_name
        self.parameters = parameters


class IfNode(ASTNode):
    '''If statement node.

        if odd 1 then begin
            write(1);
        end

    :param condition: condition expression node.
    :param then_part: then statement node.
    :param else_part: else statement node.
    '''

    def __init__(self, condition, then_part, else_part):
        self.condition = condition
        self.then_part = then_part
        self.else_part = else_part


class ConditionNode(ASTNode):
    '''If condition node.

    :param operator: operator.
    :param left_expression: left expression.
    :param right_expression: right expression.
    '''

    def __init__(self, operator, left_expression, right_expression):
        self.operator = operator
        self.left_expression = left_expression
        self.right_expression = right_expression


class WhileNode(ASTNode):
    '''While statement node.

        while num > 0 begin
            num = num - 1;
        end

    :param condition: condition expression node.
    :param body: loop body.
    '''

    def __init__(self, condition, body):
        self.condition = condition
        self.body = body


class AssignmentNode(ASTNode):
    '''Assignment node.

        a := 1

    :param name: assignee identity node.
    :param expression: assigned expression.
    '''
    def __init__(self, name, expression):
        self.name = name
        self.expression = expression


class IdentNode(ASTNode):
    '''Identity node.

    :param name: identity's name
    '''

    def __init__(self, name):
        self.name = name

    def __str__(self):
        return '<IdentNode: {0}>'.format(self.name)


class UnaryNode(ASTNode):
    '''Unary expression node.

        - num

    :param operator: operator.
    :param expression: expression node.
    '''

    def __init__(self, operator, expression):
        self.operator = operator
        self.expression = expression


class BinaryNode(ASTNode):
    '''Binary operation expression node.

        a / b

    :param operator: operator.
    :param left: left side expression node.
    :param right: right side expression node.
    '''

    def __init__(self, operator, left, right):
        self.operator = operator
        self.left = left
        self.right = right


class Parser(object):
    '''Parser.'''

    def __init__(self):
        # Lexer instance.
        self.lexer = None

    def _expect(self, token_type):
        '''Check and consume a token from lexer.
        Raises `CompileError` when token type mismatch.

        :param token_type: expected token type.
        '''
        if self.lexer is None:
            raise CompileError('Lexer not set yet.')
        # Don't use it yet so the caller can reuse it later.
        token = self.lexer.peek()
        if token.type != token_type:
            raise CompileError('Expect type: {0}, got: {1}'.format(token_type,
                                                                   token))
        return self.lexer.get_token()  # Throw the token.

    def __call__(self, lexer):
        return self.parse(lexer)

    def parse(self, lexer):
        '''Create a parse tree.

        :param lexer: lexer instance.
        '''
        self.lexer = lexer

        return self.parse_program()

    def parse_program(self):
        '''Parse `program` node.'''
        program = ProgramNode(self.parse_block())
        self._expect(TokenType.PERIOD)
        return program

    def parse_block(self):
        '''Parse `block` node.'''
        const_nodes = []
        var_nodes = []
        procedure_nodes = []
        statements = None

        token = self.lexer.peek()
        if token.type == TokenType.CONST:
            const_nodes = self.parse_consts()
            token = self.lexer.peek()

        if token.type == TokenType.VAR:
            var_nodes = self.parse_vars()

        procedure_nodes = self.parse_procedures()
        statements = self.parse_statement()
        if not isinstance(statements, list):
            statements = [statements]

        return BlockNode(const_nodes, var_nodes, procedure_nodes, statements)

    def parse_consts(self):
        '''Parse `const` declarations.'''
        self._expect(TokenType.CONST)

        const_nodes = []

        # Parse first const node.
        const_nodes.append(self.parse_const())

        # Parse remained const nodes.
        while True:
            node = self.lexer.peek()
            if node.type != TokenType.COMMA:
                break
            self.get_token()
            const_nodes.append(self.parse_const())

        self._expect(TokenType.SEMI)

        return const_nodes

    def parse_const(self):
        '''Parse a `const` node.'''
        ident = self._expect(TokenType.IDENT)
        self._expect(TokenType.EQ)
        # TODO symbol table
        self._expect(TokenType.NUM)

        return ConstNode(ident)

    def parse_vars(self):
        '''Parse `var` declarations.'''
        self._expect(TokenType.VAR)

        var_nodes = []

        # Parse first var node.
        var_nodes.append(self.parse_var())

        # Parse remained var nodes.
        while True:
            node = self.lexer.peek()
            if node.type != TokenType.COMMA:
                break
            self.lexer.get_token()
            var_nodes.append(self.parse_var())

        self._expect(TokenType.SEMI)

        return var_nodes

    def parse_var(self):
        '''Parse a `var` node.'''
        # TODO symbol table
        name = self._expect(TokenType.IDENT)

        return VarNode(name)

    def parse_procedures(self):
        '''Parse `procedure` declarations.'''
        procedure_nodes = []
        while True:
            token = self.lexer.peek()
            if token.type != TokenType.PROCEDURE:
                break
            procedure_nodes.append(self.parse_procedure())

        return procedure_nodes

    def parse_procedure(self):
        '''Parse a `procedure` node.'''
        self._expect(TokenType.PROCEDURE)
        name = self._expect(TokenType.IDENT)
        self._expect(TokenType.SEMI)
        block = self.parse_block()
        self._expect(TokenType.SEMI)

        return ProcedureNode(name, block)

    def parse_statement(self):
        '''Parse `statement` node.'''
        token = self.lexer.peek()

        if token.type == TokenType.IDENT:
            return self.parse_assignment()
        elif token.type == TokenType.CALL:
            return self.parse_call_procedure()
        elif token.type == TokenType.BEGIN:
            return self.parse_statements()
        elif token.type == TokenType.IF:
            return self.parse_if()
        elif token.type == TokenType.WHILE:
            return self.parse_while()
        elif token.type == TokenType.READ:
            return self.parse_read()
        elif token.type == TokenType.WRITE:
            return self.parse_write()

        raise CompileError('Unknown token: {0}'.format(token))

    def parse_statements(self):
        '''Parse compunded statements.'''
        self._expect(TokenType.BEGIN)
        statement_nodes = []

        # Parse first statement.
        statement_nodes.append(self.parse_statement())

        while True:
            token = self.lexer.peek()
            if token.type != TokenType.SEMI:
                break
            self.lexer.get_token()
            statement_nodes.append(self.parse_statement())

        self._expect(TokenType.END)
        return statement_nodes

    def parse_assignment(self):
        '''Parse `assignment` node.'''
        # TODO symbol table
        name = self._expect(TokenType.IDENT)
        self._expect(TokenType.ASSIGN)
        expression = self.parse_expression()

        return AssignmentNode(name, expression)

    def parse_call_procedure(self):
        '''Parse call procedure node.'''
        self._expect(TokenType.CALL)
        procedure_name = self._expect(TokenType.IDENT)

        return CallUserProcedureNode(procedure_name)

    def parse_if(self):
        '''Parse if statement.'''
        self._expect(TokenType.IF)
        condition = self.parse_condition()
        then_part = self.parse_then_part()

        # TODO support else part
        else_part = None

        return IfNode(condition, then_part, else_part)

    def parse_condition(self):
        '''Parse condition.'''
        token = self.lexer.peek()
        if token.type == TokenType.ODD:
            return ConditionNode(TokenType.ODD, self.parse_expression(), None)

        left_exp = self.parse_expression()
        op = self.lexer.get_token()
        right_exp = self.parse_expression()
        return ConditionNode(op.type, left_exp, right_exp)

    def parse_then_part(self):
        '''Parse then part.'''
        self._expect(TokenType.THEN)
        return self.parse_statement()

    def parse_while(self):
        '''Parse while statement.'''
        self._expect(TokenType.WHILE)
        condition = self.parse_condition()
        self._expect(TokenType.DO)
        body = self.parse_statement()

        return WhileNode(condition, body)

    def parse_read(self):
        '''Parse read statement.'''
        self._expect(TokenType.READ)
        self._expect(TokenType.LPAREN)

        parameters = []

        parameters.append(self._expect(TokenType.IDENT))
        while True:
            token = self.lexer.peek()
            if token.type != TokenType.COMMA:
                break
            self.lexer.get_token()
            parameters.append(self._expect(TokenType.IDENT))

        self._expect(TokenType.RPAREN)

        return CallBuiltinProcedureNode(TokenType.READ, parameters)

    def parse_write(self):
        '''Parse write statement.'''
        self._expect(TokenType.WRITE)
        self._expect(TokenType.LPAREN)

        parameters = []

        parameters.append(self.parse_expression())
        while True:
            token = self.lexer.peek()
            if token.type != TokenType.COMMA:
                break
            self.lexer.get_token()
            parameters.append(self.parse_expression())

        self._expect(TokenType.RPAREN)

    def parse_expression(self):
        '''Parse an `expression` node.'''
        exp_operator_types = [TokenType.PLUS, TokenType.MINUS]

        unary_node = None
        unary_operator = self.lexer.peek()
        if unary_operator.type in exp_operator_types:
            self.lexer.get_token()
            unary_node = UnaryNode(unary_operator.type, None)

        exp_node = self.parse_term()
        while True:
            token = self.lexer.peek()
            if token.type not in exp_operator_types:
                break
            op = self.lexer.get_token()
            right_factor = self.parse_term()
            exp_node = BinaryNode(op.type, exp_node, right_factor)

        if unary_node is None:
            return exp_node
        else:
            unary_node.expression = exp_node  # Backfill parsed expression.
            return unary_node

    def parse_term(self):
        '''Parse term.'''
        term_operator_types = [TokenType.TIMES, TokenType.OVER]

        node = self.parse_factor()
        while True:
            token = self.lexer.peek()
            if token.type not in term_operator_types:
                break
            op = self.lexer.get_token()
            right_factor = self.parse_factor()
            node = BinaryNode(op.type, node, right_factor)

        return node

    def parse_factor(self):
        '''Parse factor.'''
        token = self.lexer.peek()
        if token.type == TokenType.LPAREN:
            self._expect(TokenType.LPAREN)
            return self.parse_expression()
            self._expect(TokenType.RPAREN)
        # TODO symbol table
        elif token.type in [TokenType.NUM, TokenType.IDENT]:
            return self.lexer.get_token()

        raise CompileError('Unknown token: {0}'.format(token))
