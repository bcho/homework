# coding: utf-8

import math


def is_prime(i):
    for sub in range(2, int(math.sqrt(i))):
        if i % sub == 0:
            return False
    return True


def is_palindrome(i):
    i = str(i)
    return i == i[::-1]


def find(upper):
    for i in range(upper, 1, -1):
        if is_prime(i) and is_palindrome(i):
            return i


print(find(1000))
