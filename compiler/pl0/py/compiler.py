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
    RPAREN = (23, ')')
    SEMI = (24, ';')
    PERIOD = (25, ',')
    PLUS = (26, '+')
    MINUS = (27, '-')
    TIMES = (28, '*')
    OVER = (29, '/')

    # Character
    IDENT = (30, None)
    NUM = (31, None)


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
    :param is_eof: indicates if it's a EOF. Defaults to `False`
    '''

    def __init__(self, char, is_eof=None):
        self.is_eof = is_eof or False
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
        return self.is_eof

    @_none_is_nonthing
    def __eq__(self, other):
        return self.char == other

    def __radd__(self, other):
        return other + self.char


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

    def reset(self):
        '''Reset lexer.'''
        self._line_buffer = ''
        self.lines, self.cols = 0, 0

    @property
    def tokens(self):
        '''Tokens stream.'''
        while True:
            token = self._get_token()
            if token.type is TokenType.EOF:
                raise StopIteration
            yield token

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
                    elif char == ';':
                        cur_token = self._make_token(TokenType.SEMI, ';')
                        break  # while state != LexerState.DONE
                    elif char == ',':
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
                # Skip over the comments.
                next_char = self._get_char()
                if char == '*' and next_char == ')':
                    state = LexerState.START
                elif char.iseof():
                    state = LexerState.DONE
                    cur_token = self._make_token(TokenType.ERROR,
                                                 'unexpected EOF, '
                                                 'maybe missing `*)`')

            else:
                raise CompileError('lexer: unexpected state.')

        return cur_token

    def _get_char(self):
        '''Get a token character from input stream.'''
        assert(self._input_stream is not None), 'Should setup input stream.'

        if self.cols >= len(self._line_buffer):
            self.lines += 1
            self.cols = 0
            self._line_buffer = self._input_stream.readline()
            if self._line_buffer is None or len(self._line_buffer) == 0:
                return TokenChar(None, is_eof=True)

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


if __name__ == '__main__':
    lexer = Lexer()
    for i in lexer:
        print(i)
