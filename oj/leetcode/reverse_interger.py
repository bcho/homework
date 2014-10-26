class Solution:

    def reverse(self, x):
        if x == 0:
            return 0

        abs_x = abs(x)
        return int(str(abs_x)[::-1]) * (x / abs_x)


if __name__ == '__main__':
    s = Solution()
    assert(s.reverse(0) == 0)
    assert(s.reverse(123) == 321)
    assert(s.reverse(-123) == -321)
