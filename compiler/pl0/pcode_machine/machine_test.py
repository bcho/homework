# coding: utf-8

'''
# Testcases for p-code machine.
'''

import random
import unittest

# Basic routines.
from machine import ExecuteError, panic
# Instructions.
from machine import (GET_OPCODE, GET_OP1, GET_OP2,
                     assemble_instruction, instructions)
# Machine
from machine import DoubleEndStack


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

            self.assertEqual(op_name, instructions[GET_OPCODE(inst)].name)
            self.assertEqual(op1, GET_OP1(inst))
            self.assertEqual(op2, GET_OP2(inst))

    def testAssembleInstruction(self):
        for (inst, disassembled) in self.instructions:
            assembled = assemble_instruction(*disassembled)

            self.assertEqual(inst, assembled)


class TestBuiltin(unittest.TestCase):
    pass


class TestDoubleEndStack(unittest.TestCase):

    def setUp(self):
        self.capacity = random.randint(1e2, 1e5)
        self.stack = DoubleEndStack(self.capacity)

    def testLowStack(self):
        self.assertTrue(self.stack.is_low_empty)
        self.assertFalse(self.stack.is_low_full)

        test_elem = 1
        self.stack.push_low(test_elem)
        self.assertFalse(self.stack.is_low_empty)
        self.assertEqual(test_elem, self.stack.low_top)
        self.assertEqual(test_elem, self.stack.pop_low())
        self.assertRaises(IndexError, self.stack.pop_low)

        for i in range(self.capacity):
            self.stack.push_low(test_elem)
        self.assertRaises(IndexError, self.stack.push_low, test_elem)

        self.stack.low_push_at(0, test_elem)
        self.assertEqual(test_elem, self.stack.low_get_at(0))
        self.assertRaises(IndexError, self.stack.low_get_at, -1)
        self.assertRaises(IndexError, self.stack.low_get_at, self.capacity)
        self.assertRaises(IndexError, self.stack.low_push_at, -1, test_elem)
        self.assertRaises(IndexError, self.stack.low_push_at,
                          self.capacity, test_elem)

    def testHighStack(self):
        self.assertTrue(self.stack.is_high_empty)
        self.assertFalse(self.stack.is_high_full)

        test_elem = 1
        self.stack.push_high(test_elem)
        self.assertFalse(self.stack.is_high_empty)
        self.assertEqual(test_elem, self.stack.high_top)
        self.assertEqual(test_elem, self.stack.pop_high())
        self.assertRaises(IndexError, self.stack.pop_high)

        for i in range(self.capacity):
            self.stack.push_high(test_elem)
        self.assertRaises(IndexError, self.stack.push_high, test_elem)

        self.stack.high_push_at(0, test_elem)
        self.assertEqual(test_elem, self.stack.high_get_at(0))
        self.assertRaises(IndexError, self.stack.high_get_at, -1)
        self.assertRaises(IndexError, self.stack.high_get_at, self.capacity)
        self.assertRaises(IndexError, self.stack.high_push_at, -1, test_elem)
        self.assertRaises(IndexError, self.stack.high_push_at,
                          self.capacity, test_elem)

    def testOverflow(self):
        '''Apply some random test for stack.'''
        low_end_to_push = random.randint(0, self.capacity)
        boundary = low_end_to_push
        high_end_to_push = self.capacity - low_end_to_push

        low_end_pushed, high_end_pushed = [], []

        # Should not overflow during the push.
        while low_end_to_push > 0 and high_end_to_push > 0:
            low, high = random.random(), random.random()
            low_end_pushed.append(low)
            high_end_pushed.append(high)

            who_first = random.randint(0, 2)
            if who_first == 1:
                self.stack.push_low(low)
                self.stack.push_high(high)
            else:
                self.stack.push_high(high)
                self.stack.push_low(low)

            self.assertEqual(self.stack.low_top, low)
            self.assertEqual(self.stack.high_top, high)

            low_end_to_push -= 1
            high_end_to_push -= 1
        while low_end_to_push > 0:
            low = random.random()
            low_end_pushed.append(low)
            self.stack.push_low(low)
            self.assertEqual(self.stack.low_top, low)
            low_end_to_push -= 1
        while high_end_to_push > 0:
            high = random.random()
            high_end_pushed.append(high)
            self.stack.push_high(high)
            self.assertEqual(self.stack.high_top, high)
            high_end_to_push -= 1

        # Should throw overflow.
        self.assertTrue(self.stack.is_low_full)
        self.assertTrue(self.stack.is_high_full)
        self.assertRaises(IndexError, self.stack.push_low, random.random())
        self.assertRaises(IndexError, self.stack.push_high, random.random())

        # Should raise error when get/put at boundary.
        self.assertRaises(IndexError, self.stack.low_get_at, boundary)
        self.assertRaises(IndexError, self.stack.low_push_at, boundary, 1)
        self.assertRaises(IndexError, self.stack.high_push_at, boundary - 1, 1)

        # Check stack sequence.
        low_end_pushed.reverse()
        for i in low_end_pushed:
            self.assertEqual(i, self.stack.pop_low())
        high_end_pushed.reverse()
        for i in high_end_pushed:
            self.assertEqual(i, self.stack.pop_high())
        self.assertTrue(self.stack.is_low_empty)
        self.assertTrue(self.stack.is_high_empty)

    def testLowIndexMoveTo(self):
        fill_value = 1

        # Should raise exception in boundary cases.
        self.assertRaises(IndexError, self.stack.low_move_to, -1, fill_value)
        self.assertRaises(IndexError, self.stack.low_move_to, self.capacity,
                          fill_value)

        self.stack.low_move_to(0, fill_value)
        self.assertEqual(0, self.stack.low_top_index)

        self.stack.low_move_to(self.capacity - 1, fill_value)
        while not self.stack.is_low_empty:
            self.assertEqual(fill_value, self.stack.pop_low())

    def testHighIndexMoveTo(self):
        fill_value = 1

        # Should raise exception in boundary cases.
        self.assertRaises(IndexError, self.stack.high_move_to, -1, fill_value)
        self.assertRaises(IndexError, self.stack.high_move_to,
                          self.capacity, fill_value)

        self.stack.high_move_to(self.capacity - 1, fill_value)
        self.assertEqual(self.capacity - 1, self.stack.high_top_index)

        self.stack.low_move_to(0, fill_value)
        while not self.stack.is_high_empty:
            self.assertEqual(fill_value, self.stack.pop_high())

    def testMoveToBoundary(self):
        fill_value = 1
        boundary = random.randint(0, self.capacity)

        self.stack.low_move_to(boundary, fill_value)
        self.assertRaises(IndexError, self.stack.high_move_to, boundary,
                          fill_value)

        self.stack.reset()

        self.stack.high_move_to(boundary, fill_value)
        self.assertRaises(IndexError, self.stack.low_move_to, boundary,
                          fill_value)


if __name__ == '__main__':
    unittest.main()
