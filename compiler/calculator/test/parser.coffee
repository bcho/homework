should = require 'should'
{
  Parser: Parser,
  TokenType: TokenType
} = require '../calc'

describe 'Parser', ->
  parser = new Parser

  it 'should parse program with correct lines', ->
    lines = parseInt Math.random() * 100 % 100 + 1, 10
    stream = ('1 + 1' for i in [lines..1]).join '\n'

    linesNode = parser.parse stream
    linesNode.lines.length.should.be.exactly lines

  it 'should parse simple formula', ->
    stream = '1 + 1'

    lineNode = (parser.parse stream).lines[0]
    lineNode.left.item.getValue().should.be.exactly '1'
    lineNode.op.should.be.exactly TokenType.PLUS
    lineNode.right.item.getValue().should.be.exactly '1'

  describe 'should parse formula with correct association', ->
    stream = '1 + 2 * 5 ^ (3 + 4)'

    lineNode = (parser.parse stream).lines[0]

    it 'should parse 1 + correctly', ->
      lineNode.left.item.getValue().should.be.exactly '1'
      lineNode.op.should.be.exactly TokenType.PLUS

    it 'should parse 2 * correctly', ->
      lineNode = lineNode.right
      lineNode.left.item.getValue().should.be.exactly '2'
      lineNode.op.should.be.exactly TokenType.TIMES

    it 'should parse 5 ^ correctly', ->
      lineNode = lineNode.right
      lineNode.left.item.getValue().should.be.exactly '5'
      lineNode.op.should.be.exactly TokenType.POW

    it 'should parse 3 + 4 correctly', ->
      lineNode = lineNode.right
      lineNode.left.item.getValue().should.be.exactly '3'
      lineNode.op.should.be.exactly TokenType.PLUS
      lineNode.right.item.getValue().should.be.exactly '4'

  it 'should parse assignment', ->
    stream = 'let a = 1 + 2'

    lineNode = (parser.parse stream).lines[0]

    lineNode.ident.getValue().should.be.exactly 'a'
    (lineNode.symbolTable.has 'a').should.be.true
    lineNode.exp.left.item.getValue().should.be.exactly '1'
    lineNode.exp.op.should.be.exactly TokenType.PLUS
    lineNode.exp.right.item.getValue().should.be.exactly '2'

  it 'should not parse malformed formula', ->
    streams = [
      '1 +',
      '+ 2',
      '1 + /',
      # TODO these ttwo should be valid.
      # '+ 1 / 2',
      # '- 2 + 3',
      '1 - (2 + 3))',
      '1 - 2 / 3)',
      'let a = ',
      'a = 1',
      'a + b = 1',
      'let 1 = 2'
    ]

    for stream in streams
      (-> parser.parse stream).should.throw()
