#coding: utf-8


def comb(sequences, r, cb):
    def helper(current, remains, current_r, r, callback):
        if len(current) == r:
            callback(current)
            return

        for i in xrange(0, len(remains) - current_r + 1):
            current.append(remains[i])
            helper(current, remains[i + 1:], current_r - 1, r, callback)
            current.pop(-1)

    assert len(sequences) >= r

    helper([], sequences, r, r, cb)


def perm(sequences, r, cb):
    def helper(current, remains, current_r, r, callback):
        if len(current) == r:
            callback(current)
            return

        for i in xrange(0, len(remains)):
            current.append(remains.pop(i))
            helper(current, remains, current_r - 1, r, callback)
            remains.insert(i, current.pop(-1))

    assert len(sequences) >= r

    helper([], sequences, r, r, cb)


if __name__ == '__main__':
    import sys
    import pprint
    n, r = int(sys.argv[-2]), int(sys.argv[-1])
    comb(list(xrange(1, n + 1)), r, pprint.pprint)
    print '--------'
    perm(list(xrange(1, n + 1)), r, pprint.pprint)
