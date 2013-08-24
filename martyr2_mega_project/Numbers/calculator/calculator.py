#coding: utf-8

'''**Calculator** ¨C A simple calculator to do basic operators.'''


import operator as OP


class Stack(list):

    def is_empty(self):
        return len(self) == 0

    def top(self):
        self._check_size()

        return self[0]

    def pop(self):
        self._check_size()

        top = self.top()
        self.remove(top)

        return top

    def pop2(self):
        rc = self.pop()
        lc = self.pop()

        return (lc, rc)

    def push(self, value):
        self.insert(0, value)

    def _check_size(self):
        if self.is_empty():
            raise IndexError


class OpStack(Stack):
    pass


class NumStack(Stack):

    def push(self, value):
        super(NumStack, self).push(value)


class Calculator(object):
    ops = '+ - x * /'.split()
    opr = dict(zip(ops, [0, 0, 1, 1, 1]))
    opf = dict(zip(ops,
        [OP.add, OP.sub, OP.mul, OP.mul, OP.div]))

    def parse(self):

        def is_op(c):
            return c in self.ops

        def is_num(c):
            try:
                int(c)
                return True
            except ValueError:
                return False
            return False

        def is_blank(c):
            return c == ' '

        def is_left_parentheses(c):
            return c == '('
        
        def is_right_parentheses(c):
            return c == ')'

        prev_num, i = None, 0
        while i < len(self.formula):
            c = self.formula[i]

            if is_blank(c):
                if prev_num:
                    self.num_stack.push(prev_num)
                    prev_num = None
            elif is_op(c):
                if prev_num:
                    self.num_stack.push(prev_num)
                    prev_num = None

                while not self.op_stack.is_empty() and \
                        self.opr[c] <= self.opr[self.op_stack.top()]:
                    self._compute_top()

                self.op_stack.push(c)
            elif is_left_parentheses(c):
                if prev_num:
                    self.num_stack.push(prev_num)
                    prev_num = None

                right = self.formula.rfind(')')
                if right == -1:
                    raise FormulaError

                sub, i = Calculator(self.formula[i + 1:right]), right
                self.num_stack.push(sub.compute())
            elif is_num(c):
                n = int(c)
                prev_num = n if prev_num is None else prev_num * 10 + n

            i += 1
        if not prev_num is None:
            self.num_stack.push(prev_num)

    def compute(self):
        self.parse()

        while not self.op_stack.is_empty():
            self._compute_top()
        
        return self.num_stack.top()

    def _compute(self, op, lc, rc):
        if op not in self.opf:
            raise OpeartorError
        return self.opf[op](lc, rc)

    def _compute_top(self):
        op = self.op_stack.pop()
        lc, rc = self.num_stack.pop2()
        self.num_stack.push(self._compute(op, lc, rc))

    def __init__(self, formula):
        self.op_stack = OpStack()
        self.num_stack = NumStack()
        self.formula = formula


class OpeartorError(Exception):
    pass


class FormulaError(Exception):
    pass


if __name__ == '__main__':
    formula = raw_input()
    c = Calculator(formula)
    print c.compute(), eval(formula)
