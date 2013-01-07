#coding: utf-8


def A(x, y):
    if y == 0:
        return 0
    elif x == 0:
        return 2 * y
    elif y == 1:
        return 2
    else:
        return A((x - 1), A(x, y - 1))


if __name__ == '__main__':
    print A(1, 10)
    print A(2, 4)
    print A(3, 3)
