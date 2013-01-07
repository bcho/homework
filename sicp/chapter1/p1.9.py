#coding: utf-8


def plus_recursive(a, b):
    if a == 0:
        return b
    return 1 + plus_recursive(a - 1, b)


def plus_iter(a,  b):
    if a == 0:
        return b
    return plus_iter(a - 1, b + 1)


if __name__ == '__main__':
    #: 999 will raise RuntimeError...
    print plus_recursive(998, 5)

    print plus_iter(998, 5)
