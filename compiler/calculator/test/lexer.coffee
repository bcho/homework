should = require 'should'
{
  Lexer: Lexer,
  TokenType: TokenType,
  TokenPattern: TokenPattern
} = require '../calc'

describe 'Lexer', ->
    lexer = new Lexer

    it 'should handle line breaks', ->
      lines = parseInt Math.random() * 100 % 100 + 1, 10
      stream = ('' for i in [lines..1]).join '\n'
      lexer.setStream stream

      lexer.getToken() while not lexer.isStreamFinish()

      lexer.lines.should.be.exactly lines

    it 'should handle empty input', ->
      lexer.setStream ''
      lexer.getToken().isType(TokenType.EOF).should.be.true

    it 'should parse error', ->
      lexer.setStream '&'
      lexer.getToken().isType(TokenType.ERROR).should.be.true

    it 'should continue after error', ->
      lexer.setStream '& 123'
      lexer.getToken().isType(TokenType.ERROR).should.be.true
      lexer.getToken().isType(TokenType.NUMBER).should.be.true

    it 'should parse numbers', ->
      number = "#{parseInt Math.random() * 100000 % 100000, 10}"
      lexer.setStream number
      token = lexer.getToken()

      token.isType(TokenType.NUMBER).should.be.true
      token.getValue().should.be.exactly number
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse ident', ->
      ident = 'foobar'
      lexer.setStream ident
      token = lexer.getToken()

      token.isType(TokenType.IDENT).should.be.true
      token.getValue().should.be.exactly ident
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse special idents', ->
      idents = ['a', 'a123', '_', 'a_b_c', 'a_1_c_2']
      for ident in idents
        lexer.setStream ident
        token = lexer.getToken()

        token.isType(TokenType.IDENT).should.be.true
        token.getValue().should.be.exactly ident
        token.getLines().should.be.exactly 1
        token.getCols().should.be.exactly 1

    it 'should parse plus', ->
      op = '+'
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.PLUS).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse minus', ->
      op = '-'
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.MINUS).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse times', ->
      op = '*'
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.TIMES).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse over', ->
      op = '/'
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.OVER).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse pow', ->
      op = '^'
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.POW).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1
    
    it 'should parse let', ->
      op = 'let'
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.LET).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse assignment', ->
      op = '='
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.ASSIGN).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse left parenthes', ->
      op = '('
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.LPAREN).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse right parenthes', ->
      op = ')'
      lexer.setStream op
      token = lexer.getToken()

      token.isType(TokenType.RPAREN).should.be.true
      token.getValue().should.be.exactly op
      token.getLines().should.be.exactly 1
      token.getCols().should.be.exactly 1

    it 'should parse simple expression', ->
      lexer.setStream '1 + 2 + 3 + 4 + 5'

      while not lexer.isStreamFinish()
        token = lexer.getToken()
        token.isType(TokenType.ERROR).should.be.false

    it 'should parse multiple lines expressions', ->
      lexer.setStream '''
        let a = 1 + 2 + 3 + 4 + 5
        let b = a + 15 ^2
        a * b
      '''

      while not lexer.isStreamFinish()
        token = lexer.getToken()
        token.isType(TokenType.ERROR).should.be.false

    it 'should parse line with correct token type', ->
      lexer.setStream 'let a = 1 + 5 * b'
      types = [
        TokenType.LET,
        TokenType.IDENT,
        TokenType.ASSIGN,
        TokenType.NUMBER,
        TokenType.PLUS,
        TokenType.NUMBER,
        TokenType.TIMES,
        TokenType.IDENT
      ]

      for type in types
        token = lexer.getToken()
        token.isType(type).should.be.true

    it 'should be able to peek a token', ->
      lexer.setStream 'a'
      peekToken = lexer.peekToken()
      token = lexer.getToken()

      peekToken.getType().should.be.exactly token.getType()
      peekToken.getValue().should.be.exactly token.getValue()
      peekToken.getLines().should.be.exactly token.getLines()
      peekToken.getCols().should.be.exactly token.getCols()
