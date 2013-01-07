#coding: utf-8


def pascal_recur(i, j):
    if j == 1 or j == i:
        return 1
    return pascal_recur(i - 1, j - 1) + pascal_recur(i - 1, j)


if __name__ == '__main__':
    n = 10
    for i in range(1, n):
        for j in range(1, i + 1):
            print pascal_recur(i, j),
            print ' ',
        print '\n'
