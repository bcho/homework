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
  PRINT  : 11
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
  PRINT  : /(print)/i

ReservedKeywords = [
  {pattern: TokenPattern.LET, type: TokenType.LET},
  {pattern: TokenPattern.PRINT, type: TokenType.PRINT},
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

class PrintNode extends Node
  constructor: (@exp, @symbolTable) ->

class BinaryNode extends Node
  constructor: (@left, @op, @right, @symbolTable) ->

class ItemNode extends Node
  constructor: (@item, @type, @symbolTable) ->

class UnaryNode extends Node
  constructor: (@op, @exp, @symbolTable) ->


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
      when TokenType.PRINT
        @parsePrint()
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

  parsePrint: ->
    @expect TokenType.PRINT

    new PrintNode @parseExp(), @symbolTable

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
    node = @parseUnaryExp()
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

  parseUnaryExp: ->
    op = @peek()

    switch op.getType()
      when TokenType.MINUS
        @expect TokenType.MINUS
        new UnaryNode TokenType.MINUS, @parseUnaryExp(), @symbolTable
      when TokenType.PLUS
        @expect TokenType.PLUS
        new UnaryNode TokenType.PLUS, @parseUnaryExp(), @symbolTable
      else
        @parseItem()

  parseItem: ->
    token = @peek()

    switch token.getType()
      when TokenType.LPAREN
        @expect TokenType.LPAREN
        node = @parseExp()
        @expect TokenType.RPAREN
        node
      when TokenType.NUMBER
        new ItemNode @get(), TokenType.NUMBER, @symbolTable
      when TokenType.IDENT
        new ItemNode @get(), TokenType.IDENT, @symbolTable
      else
        throw new CompileError "Unexpected token #{token}"


class Compiler

  # Symbols table.
  symbolTable: null

  constructor: ->
    @symbolTable = {}

  compile: (node) ->
    if node instanceof LinesNode
      @compileLinesNode node
    else if node instanceof AssignNode
      @compileAssignNode node
    else if node instanceof PrintNode
      @compilePrintNode node
    else if node instanceof BinaryNode
      @compileBinaryNode node
    else if node instanceof ItemNode
      @compileItemNode node
    else if node instanceof UnaryNode
      @compileUnaryNode node
    else
      throw new CompileError "Got unexpected node #{node}"

  compileUnaryNode: (node) ->
    base = if node.op is TokenType.PLUS then 1 else -1

    base * (@compile node.exp)

  compileItemNode: (node) ->
    switch node.type
      when TokenType.NUMBER
        parseInt node.item, 10
      when TokenType.IDENT
        identVal = @symbolTable[node.item.getValue()]
        if not identVal?
          throw new CompileError "Undefined variable: #{node.item}"
        identVal

  compileBinaryNode: (node) ->
    lval = @compile node.left
    rval = @compile node.right

    switch node.op
      when TokenType.PLUS
        lval + rval
      when TokenType.MINUS
        lval - rval
      when TokenType.TIMES
        lval * rval
      when TokenType.OVER
        lval / rval
      when TokenType.POW
        Math.pow lval, rval

  compilePrintNode: (node) ->
    expVal = @compile node.exp
    console.log expVal
    
    expVal

  compileAssignNode: (node) ->
    identVal = @compile node.exp
    @symbolTable[node.ident.getValue()] = identVal
    
    identVal

  compileLinesNode: (node) ->
    @compile lineNode for lineNode in node.lines


root.CompileError = CompileError
root.Token        = Token
root.TokenType    = TokenType
root.TokenPattern = TokenPattern
root.Lexer        = Lexer
root.Parser       = Parser
root.Compiler     = Compiler
