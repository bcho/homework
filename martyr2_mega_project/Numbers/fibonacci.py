#coding: utf-8

'''
Enter a number and have the program generate
the Fibonacci sequence to that number or to the Nth number.
'''


def fib():
    x1, x2 = 0, 1
    while True:
        x1, x2 = x2, x1 + x2
        yield x1


def counter(n):
    count, seq = 0, []
    for i in fib():
        count = count + 1
        seq.append(i)
        if i == n or count == n:
            return seq
    return seq


if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        print counter(int(sys.argv[1]))
