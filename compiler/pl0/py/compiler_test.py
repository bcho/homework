# coding: utf-8

'''
# Testcases for pl0 compiler.
'''

import unittest
from io import StringIO

# Token char.
from compiler import TokenChar, Token
# Lexer
from compiler import Lexer, TokenType


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

    def testSimple(self):
        stream = StringIO('(* this \nis\n comments *)\nvar var')
        lexer = Lexer(stream)

        for token in lexer:
            self.assertIsInstance(token, Token)
            self.assertEqual(TokenType.VAR, token.type)

    def testErrorState(self):
        stream = StringIO('(*')
        lexer = Lexer(stream)

        token = [i for i in lexer][0]
        self.assertIsInstance(token, Token)
        self.assertEqual(TokenType.ERROR, token.type)
