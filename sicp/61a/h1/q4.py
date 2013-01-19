#coding: utf-8


def hailstone(n):
    sequence = []
    while n != 1:
        sequence.append(n)
        if n % 2 == 0:
            n = n / 2
        else:
            n = 3 * n + 1
    sequence.append(n)

    print sequence
    return len(sequence)


def find_longest_hailstone(upper_bound):
    return max([hailstone(i) for i in xrange(2, upper_bound + 1)])


if __name__ == '__main__':
    assert hailstone(4) == 3
    print hailstone(27)

    #: it's 308
    # print find_longest_hailstone(2 ** 15)
