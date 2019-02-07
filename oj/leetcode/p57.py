# Definition for an interval.
class Interval:
    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e

    def __repr__(self):
        return f'[{self.start}, {self.end}]'

    def __str__(self):
        return f'[{self.start}, {self.end}]'


class Solution:
    def insert(self, intervals, newInterval):
        def try_merge(a, x):
            if a.start > x.start:
                a, x = x, a
            if a.end >= x.start:
                return [Interval(a.start, max(a.end, x.end))]
            return [a, x]

        def insert(rv, x):
            if not rv:
                return [x]

            ll, r = 0, len(rv) - 1
            while True:
                if ll >= r:
                    return rv[:ll] + try_merge(rv[ll], x) + rv[ll+1:]
                m = (ll + r) // 2
                if rv[m].start == x.start:
                    return rv[:m] + try_merge(rv[m], x) + rv[m+1:]
                elif rv[m].start < x.start:
                    ll = m + 1
                elif rv[m].start > x.start:
                    r = m - 1

            return rv + [x]

        rv = []
        for x in insert(intervals, newInterval):
            rv = insert(rv, x)

        return rv


s = Solution()

v = s.insert(
    [
        Interval(1, 3),
        Interval(6, 9),
    ],
    Interval(2, 5)
)
print(v)

v = s.insert(
    [
        Interval(1, 2),
        Interval(3, 5),
        Interval(6, 7),
        Interval(8, 10),
        Interval(12, 16),
    ],
    Interval(4, 8)
)
print(v)
