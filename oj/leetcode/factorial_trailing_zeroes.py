class Solution:

    def trailingZeroes(self, n):
        zeroes, s = 0, 5
        while n >= s:
            zeroes = zeroes + n / s
            s = s * 5

        return zeroes


if __name__ == '__main__':
    s = Solution()

    assert 0 == s.trailingZeroes(1)
    assert 1 == s.trailingZeroes(5)
    assert 2 == s.trailingZeroes(10)
    assert 3 == s.trailingZeroes(15)
    assert 4 == s.trailingZeroes(20)
    assert 6 == s.trailingZeroes(25)
