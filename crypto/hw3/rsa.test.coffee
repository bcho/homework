_ = window._


describe 'isPrime', ->

  it 'should return correct answer', ->
    (_.isPrime 2).should.be.true
    (_.isPrime 3).should.be.true
    (_.isPrime 5).should.be.true
    (_.isPrime 6).should.be.false
    (_.isPrime 10).should.be.false
    (_.isPrime 1517).should.be.false


describe 'randomPrime', ->

  it 'should return correct answer', ->
    (_.isPrime _.randomPrime 2, 2).should.be.true
    (_.isPrime _.randomPrime 2, 100).should.be.true
    (_.isPrime _.randomPrime 2, 10000).should.be.true


describe 'gcd', ->

  it 'should return correct answer', ->
    (_.gcd 2, 5).should.be.exactly 1
    (_.gcd 2, 10).should.be.exactly 2
    (_.gcd 2, 1517).should.be.exactly 1
    (_.gcd 37, 1517).should.be.exactly 37


describe 'modularInverse', ->

  it 'should return correct answer', ->
    (_.modularInverse 3, 11).should.be.exactly 4
    (_.modularInverse 17, 3120).should.be.exactly 2753


describe 'modularExp', ->

  it 'should return correct answer', ->
    (_.modularExp 4, 13, 497).should.be.exactly 445


describe 'rsa', ->
  @timeout 5000  # 5 seconds

  it 'should return encrypt & descrpt correctly', ->
    for i in [1..10]
      privateKey = generatePrivateKey()
      message = _.random 1, 100000
      encryptedMessage = privateKey.encrypt message

      (privateKey.decrypt encryptedMessage).should.be.exactly message
