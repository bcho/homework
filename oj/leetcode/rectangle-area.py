class Solution:

    def computeArea(self, A, B, C, D, E, F, G, H):

        class Rectangle(object):

            def __init__(self, lbx, lby, rtx, rty):
                self.lbx, self.lby = lbx, lby
                self.rtx, self.rty = rtx, rty
                self.width = abs(rtx - lbx)
                self.height = abs(rty - lby)

            @property
            def area(self):
                return self.width * self.height

            def overlap(self, other):
                return not (
                    # C < E
                    self.rtx < other.lbx or
                    # G < A
                    other.rtx < self.lbx or
                    # H < B
                    other.rty < self.lby or
                    # D < F
                    self.rty < other.lby
                )

        r1, r2 = Rectangle(A, B, C, D), Rectangle(E, F, G, H)

        if not r1.overlap(r2):
            return r1.area + r2.area
        else:
            overlap_r = Rectangle(
                max(r1.lbx, r2.lbx),
                max(r1.lby, r2.lby),
                min(r1.rtx, r2.rtx),
                min(r1.rty, r2.rty)
            )
            return r1.area + r2.area - overlap_r.area


if __name__ == '__main__':
    s = Solution()

    a = s.computeArea(-5, -2, 5, 1, -3, -3, 3, 3)
    assert 48 == a

    a = s.computeArea(-2, -2, 2, 2, -2, -2, 2, 2)
    assert 16 == a

    a = s.computeArea(-5, -2, -3, 1, -3, -3, 3, 3)
    assert 42 == a

    a = s.computeArea(-5, -5, -3, 5, -3, -3, 3, 3)
    assert 56 == a

    a = s.computeArea(-2, -2, 2, 2, -3, -3, 3, -1)
    assert 24 == a

    a = s.computeArea(-3, 0, 3, 4, 0, -1, 9, 2)
    assert 45 == a

    a = s.computeArea(-3, 0, 3, 4, 3, -1, 9, 2)
    assert 42 == a

    a = s.computeArea(0, 0, 5, 5, 1, 1, 2, 2)
    assert 25 == a

    a = s.computeArea(-2, -2, 2, 2, -2, -4, 2, -2)
    assert 24 == a
