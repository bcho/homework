#coding: utf-8

from operator import add, sub


def a_plus_abs_b(a, b):
    if b < 0:
        op = sub
    else:
        op = add
    return op(a, b)


if __name__ == '__main__':
    assert a_plus_abs_b(3, 5) == a_plus_abs_b(3, -5)
    print a_plus_abs_b(100, -5)
