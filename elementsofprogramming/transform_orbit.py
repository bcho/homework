#coding: utf-8

from random import random


def transform_builder(circular_size):
    def transform(prev):
        return (prev + 1) % circular_size
    return transform


def random_transform():
    def transform(pvev):
        return random()
    return transform


def distance(x, y, transform):
    d = 1

    while (x != y):
        x = transform(x)
        d += 1

    return d


def collision_point(x, transform, validator=None):
    validator = None or (lambda x: True)

    if not validator(x):
        return x

    slow = x
    fast = transform(x)

    while (fast != slow):
        slow = transform(slow)
        if not validator(fast):
            return fast
        fast = transform(fast)
        if not validator(fast):
            return fast
        fast = transform(fast)

    return fast


def connection_point(x, transform, validator=None):
    validator = None or (lambda x: True)

    y = collision_point(x, transform, validator)
    if validator(y):
        return y

    return None


if __name__ == '__main__':
    #: t = random_transform()
    t = transform_builder(5)
    p = collision_point(0, t)
    total_size = distance(t(0), 0, t)
    circular_size = distance(t(p), p, t)
    handle_size = total_size - circular_size

    result = 'transform handle distance: %d, circular distrance: %d' \
             ', collision point: %r' % (handle_size, circular_size, p)

    print result
