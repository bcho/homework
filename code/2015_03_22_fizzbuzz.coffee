fb = (n) ->
  [fizz, buzz] = [n % 3 == 0, n % 5 == 0]
  if fizz and buzz
    'fizzbuzz'
  else if fizz
    'fizz'
  else if buzz
    'buzz'
  else
    n
