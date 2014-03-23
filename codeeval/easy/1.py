# coding: utf-8


def read():
    import sys

    def clean_line(line):
        return list(map(int, line.split(' ')))

    with open(sys.argv[1], 'r') as test_cases:
        lines = [clean_line(test) for test in test_cases]

    return lines


def count(line):
    F, B, upper = line

    def choose(i):
        x = ''
        if i % F == 0:
            x = 'F'
        if i % B == 0:
            x = '{0}B'.format(x)
        if x == '':
            x = '{0}'.format(i)
        return x

    return [choose(i) for i in range(1, upper + 1)]


print('\n'.join((' '.join(count(i)) for i in read())))
