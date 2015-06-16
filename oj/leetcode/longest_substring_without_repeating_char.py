class Solution:

    def lengthOfLongestSubstring(self, s):
        rv = -1
        i = 0
        while True:
            if i >= len(s):
                break
            found = {s[i]: True}
            for j in range(i + 1, len(s)):
                if s[j] in found:
                    rv = max(rv, j - i)
                    break
            i = i + 1

        return rv


if __name__ == '__main__':
    s = Solution()

    assert 1 == s.lengthOfLongestSubstring('bbbbbb')
    assert 3 == s.lengthOfLongestSubstring('abcabcbb')
