#coding: utf-8


def two_of_three(a, b, c):
    return a ** 2 + b ** 2 + c ** 2 - min([a, b, c]) ** 2


if __name__ == '__main__':
    print two_of_three(3, 4, 5)
    assert two_of_three(3, 4, 5) == 41
    assert two_of_three(3, 4, 4) == 32
    assert two_of_three(3, 3, 3) == 18
