#coding: utf-8


def fib_r(k):

    def fib(i):
        assert i > 0

        if i == 1:
            return 1
        elif i == 2:
            return 1
        else:
            return fib(i - 1) + fib(i - 2)

    return [fib(i) for i in xrange(1, k + 1, 1)]


def fib_nr(k):
    assert k > 0

    a1, a2, i = 1, 1, 1

    while i <= k:
        if i == 1 or i == 2:
            yield 1
        else:
            yield a1 + a2
            a1, a2 = a2, a1 + a2
        i = i + 1


if __name__ == '__main__':
    print fib_r(15)
    print list(fib_nr(15))
