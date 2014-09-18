class CompileError

  name: 'compile error'

  constructor: (@message) ->



# Lexical Tokens

class Token

  constructor: (@type, @value, @position) ->

  getType: -> @type
  getValue: -> @value
  getPosition: -> @position

  isType: (type) -> @type == type


Token.NUMBER = 'NUMBER'
Token.OPERATOR = 'OPERATOR'


Token.patterns =
  'NUMBER'   : /([0-9]+)/i
  'OPERATOR' : /(\+|\-)/i



# AST Nodes

class Node


class FormulaNode extends Node
  
  constructor: (@number, @formulaMinus) ->


class FormulaMinusNode extends Node

  constructor: (@op, @formula) ->


class NumberNode extends Node

  constructor: (@number) ->


class EmptyNode extends Node


# No more input. 
class EndOfTokenStreamError



class Lexer

  # Lexical patterns.
  patterns: null

  # Stream content.
  stream: ''

  # Current position.
  position: 0

  # Current token.
  token: null

  # White space regex.
  whiteSpacePattern: /[ \t]*/

  constructor: (@patterns) ->

  # Start token stream.
  start: (@stream) ->
    @position = 0
    @token = null
    @advance()

  # Get current token.
  getToken: ->
    throw new EndOfTokenStreamError if @isStreamFinish()
    @token

  # Parse next token.
  advance: ->
    @position += @token.getValue().length if @token?
    
    return if @isStreamFinish()

    # Skip white spaces.
    whiteSpaces = @whiteSpacePattern.exec @getStream()
    @position += whiteSpaces[0].length if whiteSpaces?

    for type, pattern of @patterns
      match = pattern.exec @getStream()

      # Should match the cloest token from stream.
      continue unless match? and match.index == 0

      value = match[0]
      @token = new Token type, value, @position
      return @token

    # Handle error here.

  expect: (tokenType) ->
    if not @token? or not @token.isType tokenType
      throw new CompileError "expect type: #{tokenType}, got '#{@getStream()}'"

    @token

  isStreamFinish: ->
    @position >= @stream.length

  getStream: ->
    return '' if @isStreamFinish()
    @stream[@position..]


# Grammar:
#
#   Formula  -> Number Formula'
#   Formula' -> Operator Formula | e
#
# After parsing, we will have tree like this:
#
#       Formula
#       |      \
#     Number  Forumla'
#             |      \
#           Oper     Formula
#
# But it should be
#
#       Operator
#       |       \
#    Formula    Operator
#               |      \
#             Formula  Formula
#
# Which will make the compiler happy.
class Parser

  constructor: (@lexer) ->

  parseFormula: ->
    numberToken = @lexer.expect Token.NUMBER
    numberNode = new NumberNode numberToken

    @lexer.advance()

    new FormulaNode numberNode, @parseFormulaMinus()

  parseFormulaMinus: () ->
    return new EmptyNode if @lexer.isStreamFinish()

    operatorToken = @lexer.expect Token.OPERATOR

    @lexer.advance()
    new FormulaMinusNode operatorToken, @parseFormula()


# No instructions generator :)
Compiler =

  compile: (node) ->
    if node instanceof NumberNode
      @compileNumberNode node
    else if node instanceof FormulaNode
      @compileFormulaNode node
    else
      console.log node
      throw new CompileError "compile error: unknown node: #{node}"

  # FIXME should transform the AST in parser.
  compileFormulaNode: (node) ->
    left = @compileNumberNode node.number

    while node.formulaMinus instanceof FormulaMinusNode
      formulaMinus = node.formulaMinus
      op = formulaMinus.op.getValue()
      formulaMinusFormula = formulaMinus.formula
      right = @compileNumberNode formulaMinusFormula.number

      switch op
        when '-'
          left = left - right
        when '+'
          left = left + right

      node = formulaMinusFormula

    left


  compileNumberNode: (node) ->
    parseInt node.number.getValue(), 10



lexer = new Lexer Token.patterns

# Usage: node main.js 1 + 2 + 3 + 4
input = process.argv.slice(2).join(' ') || '1 + 41'

lexer.start input
parser = new Parser lexer

root = parser.parseFormula()
console.log "#{input} = #{Compiler.compile root}"
