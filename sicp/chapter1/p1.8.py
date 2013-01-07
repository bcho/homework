#coding: utf-8


def good_enough(guess, x):
    return abs(x - guess ** 3) < 0.001


def improve(guess, x):
    return (x / guess ** 2 + 2 * guess) / 3


def cube_sqrt_iter(guess, x):
    if good_enough(guess, x):
        return guess
    return cube_sqrt_iter(improve(guess, x), x)


def cube_sqrt(x):
    return cube_sqrt_iter(1.0, x)


if __name__ == '__main__':
    print cube_sqrt(27)
