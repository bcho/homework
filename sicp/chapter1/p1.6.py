#coding: utf-8


def new_if(cond, then_clause, else_clause):
    return then_clause if cond else else_clause


def good_enough(guess, x):
    return abs(x - guess ** 2) < 0.001


def improve(guess, x):
    return (guess + x / guess) / 2


def sqrt_iter(guess, x):
    return new_if(good_enough(guess, x),
                  guess,
                  sqrt_iter(improve(guess, x), x))


def sqrt(x):
    return sqrt_iter(1.0, x)


if __name__ == '__main__':
    print sqrt(100 + 37)
