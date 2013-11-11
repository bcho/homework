#coding: utf-8

import unittest

from assembler import SymbolTable, Code, Parser, Command


class SymbolTableTest(unittest.TestCase):

    def testAddEntry(self):
        table = SymbolTable()
        self.assertRaises(KeyError, table.addEntry, 'abc', '1')

    def testContains(self):
        table = SymbolTable()
        self.assertFalse(table.contains('abc'))

        table.addEntry('abc', 123)
        self.assertTrue(table.contains('abc'))

        table.addEntry('abc', 456)
        self.assertTrue(table.contains('abc'))

    def testGetAddress(self):
        table = SymbolTable()
        self.assertRaises(KeyError, table.GetAddress, 'abc')

        table.addEntry('abc', 123)
        self.assertEqual(123, table.GetAddress('abc'))

        table.addEntry('abc', 456)
        self.assertNotEqual(123, table.GetAddress('abc'))
        self.assertEqual(456, table.GetAddress('abc'))


class CodeTest(unittest.TestCase):

    def setUp(self):
        self.coder = Code()

    def testDest(self):
        self.assertEqual(0b000, self.coder.dest('null'))
        self.assertEqual(0b001, self.coder.dest('M'))

    def testComp(self):
        self.assertEqual(0b0101010, self.coder.comp('0'))
        self.assertEqual(0b0001111, self.coder.comp('-D'))

    def testJump(self):
        self.assertEqual(0b000, self.coder.jump('null'))
        self.assertEqual(0b101, self.coder.jump('JNE'))


class CommandTest(unittest.TestCase):

    def testCommand(self):
        for c in ['@abc', '@123', '@def123', '@123def', u'@abc',
                  '@abc']:
            command = Command(c)
            self.assertEqual('A_COMMAND', command.type)

        command = Command('@abc')
        self.assertEqual('abc', command.value)

        for c in ['(abc)', '(def)', '(a)', u'(abc)']:
            command = Command(c)
            self.assertEqual('L_COMMAND', command.type)

        command = Command('(abc)')
        self.assertEqual('abc', command.value)

        for c in ['dest=comp;JMP', 'comp', 'comp;JMP', 'comp;JGE',
                  'dest = comp; JLE', u'comp']:
            command = Command(c)
            self.assertEqual('C_COMMAND', command.type)

        command = Command('dest=comp;JMP')
        self.assertEqual(('dest', 'comp', 'JMP'), command.value)
        command = Command('comp')
        self.assertEqual(('null', 'comp', 'null'), command.value)
        command = Command('dest = comp')
        self.assertEqual(('dest', 'comp', 'null'), command.value)
        command = Command('comp;JGE')
        self.assertEqual(('null', 'comp', 'JGE'), command.value)

        for c in ['(abc)123', '123(abc)', '(133)', 'dest=', ';JMP',
                  'dest=comp;', 'dest=comp;jump']:
            self.assertRaises(ValueError, Command, c)


class ParserTest(unittest.TestCase):

    def testInit(self):
        Parser('')
        Parser(open('./tests.py'))

    def testCleanLine(self):
        self.assertEqual(None, Parser.cleanLine(''))
        self.assertEqual('123', Parser.cleanLine('123'))
        self.assertEqual(None, Parser.cleanLine('// 123'))
        self.assertEqual(None, Parser.cleanLine('//123'))
        self.assertEqual('123', Parser.cleanLine('123//123'))
        self.assertEqual('123', Parser.cleanLine('123 //123'))
        self.assertEqual('123', Parser.cleanLine('123 // 123'))

    def testHasMoreCommandsAndAdvance(self):
        parser = Parser('')
        self.assertFalse(parser.hasMoreCommands)

        parser = Parser('hello')
        self.assertEqual(None, parser.currentCommand)
        self.assertTrue(parser.hasMoreCommands)
        parser.advance()
        self.assertFalse(parser.hasMoreCommands)
        self.assertRaises(EOFError, parser.advance)

        parser = Parser('// this is a comment')
        self.assertFalse(parser.hasMoreCommands)

        parser = Parser('foobar // this is a command')
        self.assertTrue(parser.hasMoreCommands)

    def testSymbol(self):
        parser = Parser('@abc')
        parser.advance()
        self.assertEqual('abc', parser.symbol)

        parser = Parser('(abc)')
        parser.advance()
        self.assertEqual('abc', parser.symbol)

        parser = Parser('foobar')
        parser.advance()
        self.assertRaises(RuntimeError, lambda: parser.symbol)

    def testDestCompJump(self):
        parser = Parser('dest=comp;JMP')
        parser.advance()
        self.assertEqual('dest', parser.dest)
        self.assertEqual('comp', parser.comp)
        self.assertEqual('JMP', parser.jump)

        parser = Parser('dest = comp ; JMP')
        parser.advance()
        self.assertEqual('dest', parser.dest)
        self.assertEqual('comp', parser.comp)
        self.assertEqual('JMP', parser.jump)

        parser = Parser('dest=comp')
        parser.advance()
        self.assertEqual('dest', parser.dest)
        self.assertEqual('comp', parser.comp)
        self.assertEqual('null', parser.jump)

        parser = Parser('comp;JMP')
        parser.advance()
        self.assertEqual('null', parser.dest)
        self.assertEqual('comp', parser.comp)
        self.assertEqual('JMP', parser.jump)

        parser = Parser('comp')
        parser.advance()
        self.assertEqual('null', parser.dest)
        self.assertEqual('comp', parser.comp)
        self.assertEqual('null', parser.jump)

        parser = Parser('@abc')
        parser.advance()
        self.assertRaises(RuntimeError, lambda: parser.dest)
        self.assertRaises(RuntimeError, lambda: parser.comp)
        self.assertRaises(RuntimeError, lambda: parser.jump)


if __name__ == '__main__':
    unittest.main()
