class Token
  constructor: (@type, @value, @pos) ->


# End of stream input
class EndOfInputError


class Lexer

  # Lexical patterns.
  patterns: null

  # Input stream current position.
  position: 0

  # Input stream.
  stream: ''

  # White space regex.
  whiteSpacePattern: /[ \t]*/

  # Error token type.
  errorTokenType: 'error'

  constructor: (@patterns) ->

  setStream: (@stream) ->
    @position = 0

  getStream: ->
    return '' unless @position < @stream.length

    @stream[@position..]

  # Consume and advance stream.
  advanceStream: (steps) ->
    @position += steps

  isStreamFinish: ->
    @position >= @stream.length

  # Parse a token.
  parseToken: ->
    throw new EndOfInputError if @isStreamFinish()

    # Skip white spaces.
    whiteSpaces = @whiteSpacePattern.exec @getStream()
    @advanceStream whiteSpaces[0].length if whiteSpaces?

    for type, pattern of @patterns
      match = pattern.exec @getStream()
      
      # Should match the cloest token from stream.
      continue unless match? and match.index == 0

      value = match[0]
      token = new Token type, value, @position
      @advanceStream value.length

      return token

    # Handle lex error.
    input = @getStream()
    errorToken = new Token @errorTokenType, input, @position
    @advanceStream input.length

    errorToken

  tokenize: () ->
    tokens = []
    try
      tokens.push @parseToken() while 1
    catch EndOfInputError

    tokens


patterns =
  NUM:        /([0-9]+)/i
  PLUS:       /(\+)/i
  MINUS:      /(\-)/i


lexer = new Lexer patterns

lexer.setStream('123 + 21 - 12')

console.log lexer.tokenize()
