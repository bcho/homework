# coding: utf-8


def read():
    import sys

    with open(sys.argv[1], 'r') as test_cases:
        return [test for test in test_cases]


def reverse(line):
    return ' '.join(line.strip().split(' ')[::-1])


print('\n'.join(reverse(i) for i in read()))
