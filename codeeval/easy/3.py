# coding: utf-8

import math


def is_prime(i):
    for sub in range(2, int(math.sqrt(i))):
        if i % sub == 0:
            return False
    return True


def calculate(count):
    found = 0
    num = 2
    primes = []

    def is_prime_quick(x):
        for i in primes:
            if x % i == 0:
                return False
        return True

    while True:
        if is_prime_quick(num) and is_prime(num):
            primes.append(num)
            found = found + 1

        if found >= count:
            break

        num = num + 1

    return sum(primes)


print(calculate(1000))
