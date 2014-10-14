# coding: utf-8

'''
# Testcases for p-code machine.
'''

import unittest

# Basic routines.
from machine import ExecuteError, panic
# Instructions.
from machine import GET_OPCODE, GET_OP1, GET_OP2, instructions


class TestBasicRoutines(unittest.TestCase):

    def testPanic(self):
        self.assertRaises(ExecuteError, panic)


class TestInstructions(unittest.TestCase):

    def setUp(self):
        self.instructions = [
            (1310722, ('ENT', 0, 20)),
            (1330, ('LDC', 5, 0)),
            (3145985, ('CSP', 1, 48)),
            (1796, ('RTN', 7, 0)),
            (3, ('MST', 0, 0)),
            (0, ('CUP', 0, 0))
        ]

    def testDisassembleInstruction(self):
        for (inst, disassembled) in self.instructions:
            op_name, op1, op2 = disassembled

            self.assertEqual(instructions[op_name].opcode, GET_OPCODE(inst))
            self.assertEqual(op1, GET_OP1(inst))
            self.assertEqual(op2, GET_OP2(inst))


class TestBuiltin(unittest.TestCase):
    pass


if __name__ == '__main__':
    unittest.main()
