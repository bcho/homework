
#coding: utf-8


def good_enough(guess, prev):
    return (abs(guess - prev) / guess) < 0.001


def improve(guess, x):
    return (guess + x / guess) / 2


def sqrt_iter(guess, prev,  x):
    if good_enough(guess, prev):
        return guess
    return sqrt_iter(improve(guess, x), guess, x)


def sqrt(x):
    return sqrt_iter(1.0, 0, x)


if __name__ == '__main__':
    print sqrt(0.0001)
