root = exports ? window


class CompileError

  message: 'compile error'

  constructor: (message) ->
    @setMessage message if message?

  setMessage: (@message) ->
  getMessage: -> @message
  toString: -> @getMessage()


# Lexical Token
class Token

  constructor: (@type, @value, @lines, @cols) ->

  getType: -> @type
  getValue: -> @value
  getLines: -> @lines
  getCols: -> @cols

  isType: (type) -> @type == type

  toString: ->
    "#{@getValue()}:#{@getType()} at #{@getLines()}:#{@getCols()}"


TokenType =
  NUMBER : 0
  IDENT  : 1
  PLUS   : 2
  MINUS  : 3
  TIMES  : 4
  OVER   : 5
  POW    : 6
  LPAREN : 7
  RPAREN : 8
  LET    : 9
  ASSIGN : 10
  EOF    : 254
  ERROR  : 255

TokenPattern =
  NUMBER : /([0-9]+)/i
  IDENT  : /(([a-z]|_)([0-9]|[a-z]|_)*)/i
  PLUS   : /(\+)/i
  MINUS  : /(\-)/i
  TIMES  : /(\*)/i
  OVER   : /(\/)/i
  POW    : /(\^)/i
  LPAREN : /(\()/i
  RPAREN : /(\))/i
  LET    : /(let)/i
  ASSIGN : /(=)/i

ReservedKeywords = [
  {pattern: TokenPattern.LET, type: TokenType.LET}
]


# Lexer for calculator.
class Lexer

  # Input stream.
  stream : ''

  # Stream position.
  position: 0

  # Current cols.
  cols: 0

  # Current lines.
  lines: 1

  # Current token.
  token: null

  # White space regex.
  whiteSpacePattern: /^[ \t]*/

  # Line break regex.
  lineBreakPattern: /^\n/

  setStream: (@stream) ->
    @position = 0
    @resetStream()

  getStream: ->
    @stream[@position..]

  advanceStream: (token) ->
    token = ' ' unless token?
    
    @position += token.length
    @cols += token.length

  resetStream: ->
    @position = 0
    @lines = 1
    @cols = 1

  isStreamFinish: ->
    @position >= @stream.length

  peekToken: ->
    return @makeToken TokenType.EOF if @isStreamFinish()

    # Skip white spaces.
    whiteSpaces = @whiteSpacePattern.exec @getStream()
    @advanceStream whiteSpaces[0]

    # Skip line break.
    while @lineBreakPattern.exec @getStream()
      @position += 1
      @lines += 1
      @cols = 1

    currentContent = @getStream()
    for type, pattern of TokenPattern
      match = pattern.exec currentContent

      # Should match the cloest token from stream.
      continue unless match? and match.index == 0

      value = match[0]

      tokenType = TokenType[type]

      # Check if the ident is a reserved keyword.
      if tokenType == TokenType.IDENT
        for keyword in ReservedKeywords
          if keyword.pattern.exec value
            tokenType = keyword.type
            break
      
      token = @makeToken tokenType, value
      
      return token

    @makeToken TokenType.ERROR

  getToken: ->
    token = @peekToken()
    @advanceStream(token.value)

    token

  makeToken: (type, value) ->
    new Token type, value, @lines, @cols


# Expression type.
ExpType =
  INT: 0


# Symbol tables for calculator.
class SymbolTable

  symbols: {}

  set: (name) ->
    @symbols[name] =
      # Just have int type by now.
      type: ExpType.INT
      address: null

  get: (name) ->
    if @has name
      @symbols[name]
    else
      null

  has: (name) ->
    @symbols[name]?


# Nodes for calculator.
class Node

class LinesNode extends Node
  constructor: (@lines, @symbolTable) ->

class AssignNode extends Node
  constructor: (@ident, @exp, @symbolTable) ->

class BinaryNode extends Node
  constructor: (@left, @op, @right, @symbolTable) ->

class ItemNode extends Node
  constructor: (@item, @symbolTable) ->


# Parser for calculator.
class Parser

  lexer: null
  symbolTable: null

  constructor: ->
    @lexer = new Lexer
    @symbolTable = new SymbolTable

  # Get a token.
  get: ->
    @lexer.getToken()

  # Peek a token.
  peek: ->
    @lexer.peekToken()

  # Consume a token with expected token type.
  expect: (type) ->
    token = @lexer.getToken()
    if not token.isType(type)
      throw new CompileError "Expect type #{type}, got #{ident}"

  parse: (input) ->
    @lexer.setStream input

    @parseLines()

  parseLines: ->
    lines = []
    while true
      line = @parseLine()
      if not line
        break
      lines.push line

    new LinesNode lines, @symbolTable

  parseLine: ->
    token = @peek()
    switch token.getType()
      when TokenType.EOF
        null
      when TokenType.ERROR
        throw new CompileError token
      when TokenType.LET
        @parseAssign()
      else
        @parseExp()

  parseAssign: ->
    @expect TokenType.LET

    ident = @get()
    if not ident.isType TokenType.IDENT
      throw new CompileError "Expect ident, got #{ident}"
    @symbolTable.set ident.getValue()
    
    @expect TokenType.ASSIGN

    exp = @parseExp()

    new AssignNode ident, exp, @symbolTable

  parseExp: ->
    node = @parseTerm()

    repeat = true
    while repeat
      token = @peek()
      switch token.getType()
        when TokenType.PLUS
          @expect TokenType.PLUS
          node = new BinaryNode node, TokenType.PLUS, @parseTerm(), @symbolTable
        when TokenType.MINUS
          @expect TokenType.MINUS
          node = new BinaryNode node, TokenType.MINUS, @parseTerm(), @symbolTable
        else
          repeat = false

    node

  parseTerm: ->
    node = @parsePterm()

    repeat = true
    while repeat
      token = @peek()
      switch token.getType()
        when TokenType.TIMES
          @expect TokenType.TIMES
          node = new BinaryNode node, TokenType.TIMES, @parsePterm(), @symbolTable
        when TokenType.OVER
          @expect TokenType.OVER
          node = new BinaryNode node, TokenType.OVER, @parsePterm(), @symbolTable
        else
          repeat = false

    node

  parsePterm: ->
    node = @parseItem()
    ptermStar = @parsePtermStar()

    if ptermStar?
      new BinaryNode node, TokenType.POW, ptermStar, @symbolTable
    else
      node

  parsePtermStar: ->
    token = @peek()

    if token.isType TokenType.POW
      @expect TokenType.POW
      @parsePterm()
    else
      # eps
      null

  parseItem: ->
    token = @peek()

    switch token.getType()
      when TokenType.LPAREN
        @expect TokenType.LPAREN
        node = @parseExp()
        @expect TokenType.RPAREN
        node
      when TokenType.NUMBER
        new ItemNode @get(), @symbolTable
      when TokenType.IDENT
        new ItemNode @get(), @symbolTable
      else
        throw new CompileError "Unexpected item: #{token}"


root.CompileError = CompileError
root.Token        = Token
root.TokenType    = TokenType
root.TokenPattern = TokenPattern
root.Lexer        = Lexer
root.Parser       = Parser
