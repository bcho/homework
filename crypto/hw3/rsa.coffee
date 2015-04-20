_ = window._

# 加密配置
config =
  primes:
    min: 1000
    max: 10000


_.mixin
  # 判断是否为素数
  isPrime: (number) ->
    if number <= 3
      return number > 1
    if number % 2 == 0 or number % 3 == 0
      return false
    i = 5
    while i ** 2 <= number
      if number % i == 0 or number % (i + 2) == 0
        return false
      i += 6
    return true

  # 获取一个随机素数
  randomPrime: (min, max) ->
    while true
      prime = _.random min, max
      return prime if _.isPrime prime

  # 求最大公约数
  gcd: (a, b) ->
    return _.gcd b, a unless a > b
    if b == 0 then a else _.gcd b, a % b

  # 求模反元素
  modularInverse: (e, zn) ->
    [t, newT] = [0, 1]
    [r, newR] = [zn, e]
    while newR != 0
      quotient = r // newR
      [t, newT] = [newT, t - quotient * newT]
      [r, newR] = [newR, r - quotient * newR]
    if r > 1
      console.warn 'e is not invertible'
      return
    t += zn if t < 0
    t

  # 求幂次同余
  #
  # c = b ^ e (mod m)
  modularExp: (b, e, m) ->
    c = 1
    for ep in [1..e]
      c = (c * b) % m
    c


# 加密公钥
class PublicKey

  constructor: (@n, @e) ->

  encrypt: (m) ->
    _.modularExp m, @e, @n


# 加密密钥
class PrivateKey

  constructor: (@d, @p, @q, @zn, @publicKey) ->
    @n = @publicKey.n

  encrypt: (m) ->
    @publicKey.encrypt m

  decrypt: (c) ->
    _.modularExp c, @d, @n


# 生成一个加密密钥
generatePrivateKey = ->
  # 生成随机素数对 p, q
  p = _.randomPrime config.primes.min, config.primes.max
  q = _.randomPrime config.primes.min, config.primes.max

  n = p * q
  zn = (p - 1) * (q - 1)

  # 构造加解密参数
  while true
    e = _.random 1, zn
    if (_.gcd e, zn) == 1
      break
  d = _.modularInverse e, zn

  publicKey = new PublicKey n, e
  privateKey = new PrivateKey d, p, q, zn, publicKey

  privateKey
