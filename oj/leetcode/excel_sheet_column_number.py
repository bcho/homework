class Solution:

    def titleToNumber(self, s):
        rv = 0
        o = lambda x: ord(x) - ord('A') + 1
        for a in s:
            rv = rv * 26 + o(a)
        return rv


if __name__ == '__main__':
    s = Solution()

    assert 1 == s.titleToNumber('A')
    assert 27 == s.titleToNumber('AA')
    assert 28 == s.titleToNumber('AB')
