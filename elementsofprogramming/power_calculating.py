#coding: utf-8


def left_associated(a, times, op):
    if times == 1:
        return a
    return op(left_associated(a, times - 1, op), a)


def right_associated(a, times, op):
    if times == 1:
        return a
    return op(a, right_associated(a, times - 1, op))


def is_associatable(op, init, times=None):
    times = times or 5

    return left_associated(init, times, op) == \
            right_associated(init, times, op)


def power_accumulate(base, times, op):
    if times == 1:
        return base
    #: divide
    child = power_accumulate(base, times / 2, op)
    #: conquar
    if times % 2 == 1:
        return op(op(child, child), base)
    return op(child, child)


def mul(a, b):
    return a * b


def plus(a, b):
    return a + b


def sub(a, b):
    return a - b


if __name__ == '__main__':
    print is_associatable(sub, 5, 15)
    print is_associatable(plus, 5, 15)

    print power_accumulate(5, 5000, plus)
    print power_accumulate(5, 5000, mul)
