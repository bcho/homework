# coding: utf-8


def read():
    import sys

    def clean_line(line):
        return list(map(int, line.split(',')))

    with open(sys.argv[1], 'r') as test_cases:
        lines = [clean_line(test) for test in test_cases]

    return lines


def calculate(line):
    x, n = line
    cur = n

    while cur < x:
        cur = cur + n

    return cur


print('\n'.join(str(calculate(i)) for i in read()))
