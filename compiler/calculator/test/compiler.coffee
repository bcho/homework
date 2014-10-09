should = require 'should'
{
  Parser: Parser,
  Compiler: Compiler
} = require '../calc'

describe 'Compiler', ->
  parser = new Parser
  compiler = new Compiler

  it 'should compile simple expressions', ->
    stream = '''
    1 + 1
    2 + 3
    1 - 2
    1
    '''
    expectedResults = [
      1 + 1
      2 + 3
      1 - 2
      1
    ]
    
    (compiler.compile parser.parse stream).should.eql expectedResults

  it 'should compile complicated expressions', ->
    stream = '''
    let a = 1
    let b = 2
    let c = 3
    let d = a + b ^ c
    print d
    '''
    expectedResults = [
      1
      2
      3
      1 + Math.pow 2, 3
      1 + Math.pow 2, 3
    ]
    
    (compiler.compile parser.parse stream).should.eql expectedResults

  it 'should not compile undefined variable', ->
    stream = '''
    let a = b + 1
    '''

    (compiler.compile parser.parse stream).should.throw()
