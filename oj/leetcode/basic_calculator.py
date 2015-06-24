class Solution:

    def calculate(self, s):

        class Lexer(object):

            LP = 0
            RP = 1
            PLUS = 2
            MINUS = 3
            NUMBER = 4
            EOF = 5
            ERROR = 6

            OP_TYPE = (PLUS, MINUS)

            def __init__(self, stream):
                self.stream = stream
                self.position = 0

            def advance_stream(self, token):
                self.position = self.position + len(token)

            @property
            def is_stream_finish(self):
                return self.position >= len(self.stream)

            def take(self):
                token_type, token_value = self.peak
                if token_value:
                    self.advance_stream(token_value)
                return token_type, token_value

            @property
            def peak(self):
                while not self.is_stream_finish:
                    if self.stream[self.position] in (' ', '\t'):
                        self.position = self.position + 1
                    else:
                        break

                if self.is_stream_finish:
                    return self.EOF, None

                token_value = self.take_op()
                if token_value == '+':
                    return self.PLUS, token_value
                elif token_value == '-':
                    return self.MINUS, token_value

                token_value = self.take_parentheses()
                if token_value == '(':
                    return self.LP, token_value
                elif token_value == ')':
                    return self.RP, token_value

                token_value = self.take_number()
                if token_value:
                    return self.NUMBER, token_value

                return self.ERROR, None

            def take_op(self):
                if self.stream[self.position] in ('+', '-'):
                    return self.stream[self.position]
                else:
                    return None

            def take_parentheses(self):
                if self.stream[self.position] in ('(', ')'):
                    return self.stream[self.position]
                else:
                    return None

            def take_number(self):
                digits = '0123456789'
                pos, num = self.position, ''
                while pos < len(self.stream):
                    letter = self.stream[pos]
                    if letter in digits:
                        num = num + letter
                        pos = pos + 1
                    else:
                        break
                return num

        class Calculator(object):

            def expect(self, expected_token_type):
                token_type, _ = self.lexer.peak
                if token_type != expected_token_type:
                    raise ValueError('Unexpected {0}, expected {1}'.format(
                        token_type, expected_token_type
                    ))
                return self.lexer.take()

            def cal_expr(self):
                value = self.cal_exprp()
                while True:
                    token_type, token_value = self.lexer.peak
                    if token_type in Lexer.OP_TYPE:
                        self.lexer.take()
                        expr_value = self.cal_exprp()
                        if token_type == Lexer.PLUS:
                            value = value + expr_value
                        elif token_type == Lexer.MINUS:
                            value = value - expr_value
                    else:
                        break
                return value

            def cal_exprp(self):
                token_type, token_value = self.lexer.peak
                if token_type == Lexer.NUMBER:
                    self.lexer.take()
                    return int(token_value)
                elif token_type == Lexer.LP:
                    self.lexer.take()
                    value = self.cal_expr()
                    self.expect(Lexer.RP)
                    return value

                raise ValueError('Unexpected {0}:{1}'.format(
                    token_type, token_value
                ))

            def __call__(self, stream):
                self.lexer = Lexer(stream)
                return self.cal_expr()

        calculator = Calculator()

        return calculator(s)


if __name__ == '__main__':
    s = Solution()

    assert 23 == s.calculate('(1 + (4 + 5 +2)-3) + (6+8)')
    assert 10 == s.calculate('20 - 10')
    assert 2 == s.calculate('1 + 1')
    assert 3 == s.calculate('2-1 + 2')
    assert 1 == s.calculate('(1 + 2) + (6 -8)')
    assert 10 == s.calculate('10  ')
