#coding: utf-8

import random


INF = 1e6


def sign(e):
    if e == 0:
        raise ValueError('0 is ignored!')
    return e / abs(e)


def get_g(w):
    return lambda x, y: sign(y - x * w)


def find_mistake(points, w):
    g = get_g(w)
    for x, y, sign in points:
        if g(x, y) != sign:
            return x, sign


def correct_mistake(mistake, w):
    '''cyclic PLA'''
    x, y, sign = mistake
    iterations = 0
    while True:
        g = get_g(w)
        now = g(x, y)
        if now == sign:
            break
        w = w + now * x
        if w > INF:
            w = - random.random() * INF
        elif w < -INF:
            w = random.random() * INF
        iterations = iterations + 1
    return w, iterations


def PLA(points):
    w = sum([x for x, y, _ in points]) / len(points)  # start with average w
    iterations = 0
    while True:
        mistake = find_mistake(points, w)
        if not mistake:
            break
        w, i = correct_mistake(mistake, w)  # try to correct the mistake
        iterations = iterations + i
    return w, iterations


if __name__ == '__main__':
    print(PLA([(0, 2, 1), (2, -2, -1), (2, 3, 1), (-1.5, -2.5, -1)]))
