#coding: utf-8


def f_recur(n):
    if n <= 3:
        return n
    return f_recur(n - 1) + 2 * f_recur(n - 2) + 3 * f_recur(n - 3)


def f_iter(n):
    def _iter(a, b, c, n):
        if n <= 3:
            return c
        return _iter(b, c, 3 * a + 2 * b + c, n - 1)

    return _iter(1, 2, 3, n)


if __name__ == '__main__':
    n = 15
    print f_recur(n)
    print f_iter(n)

    print f_iter(150)
