# coding: utf-8

'''
# Testcases for pl0 compiler.
'''

import os
import unittest
from io import StringIO

# Token char.
from compiler import TokenChar, Token
# Lexer
from compiler import Lexer, TokenType
# Parser
from compiler import Parser, ProgramNode, CompileError


class TestTokenChar(unittest.TestCase):

    def testSingleCharacter(self):
        test_char = 'a'
        token_char = TokenChar(test_char)

        # Test is* method.
        for method in ('isalpha', 'isdigit', 'isspace'):
            self.assertEqual(
                getattr(test_char, method)(),
                getattr(token_char, method)(),
            )

        # Test `==` / `+` / `+=`
        self.assertTrue(test_char == token_char)
        self.assertEqual(test_char + token_char, test_char * 2)
        self.assertEqual(token_char + test_char, test_char * 2)
        another_char = test_char
        another_char += token_char
        self.assertEqual(another_char, test_char * 2)

        # Should not accept multi-character.
        self.assertRaises(TypeError, TokenChar, 'abc')

    def testNone(self):
        test_char = 'a'
        token_char = TokenChar(None)

        for method in ('isalpha', 'isdigit', 'isspace'):
            self.assertFalse(getattr(token_char, method)())

        # Test `==` / `+` / `+=`
        self.assertFalse(test_char == token_char)
        self.assertNotEqual(test_char + token_char, test_char * 2)
        self.assertNotEqual(token_char + test_char, test_char * 2)
        another_char = test_char
        another_char += token_char
        self.assertNotEqual(another_char, test_char * 2)


class TestLexer(unittest.TestCase):

    def testStream(self):
        stream = StringIO('(* this \nis\n comments *)\nvar var')
        lexer = Lexer(stream)

        for token in lexer:
            self.assertIsInstance(token, Token)
            self.assertEqual(TokenType.VAR, token.type)

    def testPeekAndGet(self):
        stream = StringIO('const a = 5')
        lexer = Lexer(stream)

        first_token = lexer.get_token()
        peeked_token = lexer.peek()
        second_token = lexer.get_token()

        self.assertEqual(TokenType.CONST, first_token.type)
        self.assertEqual(TokenType.IDENT, second_token.type)
        self.assertEqual(peeked_token, second_token)

    def testErrorState(self):
        stream = StringIO('(*')
        lexer = Lexer(stream)

        token = [i for i in lexer][0]
        self.assertIsInstance(token, Token)
        self.assertEqual(TokenType.ERROR, token.type)


class TestCompiler(unittest.TestCase):

    def setUp(self):
        self.base_dir = os.path.abspath('../samples')

    def open_samples(self, directory):
        for dirpath, __, files in os.walk(directory):
            for filename in files:
                if not filename.endswith('.pl0'):
                    continue
                full_path = os.path.join(dirpath, filename)
                with open(full_path) as f:
                    yield f

    def _parse(self, input_stream):
        return Parser().parse(Lexer(input_stream))

    def testGoodSamples(self):
        samples = os.path.join(self.base_dir, 'good')
        for sample_file in self.open_samples(samples):
            node = self._parse(sample_file)
            self.assertIsInstance(node, ProgramNode)

    def testBadSampls(self):
        samples = os.path.join(self.base_dir, 'bad')
        for sample_file in self.open_samples(samples):
            self.assertRaises(CompileError, self._parse, sample_file)
