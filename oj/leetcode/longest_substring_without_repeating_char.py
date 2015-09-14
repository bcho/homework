class Solution:

    def lengthOfLongestSubstring(self, s):
        f, rv = [0] * (len(s) + 1), 0

        for i, c in enumerate(s):
            f[i + 1] = f[i] + 1
            for j in range(i - f[i], i):
                if s[i] == s[j]:
                    f[i + 1] = i - j
                    break
            rv = max(f[i + 1], rv)

        return rv


if __name__ == '__main__':
    s = Solution()
    assert s.lengthOfLongestSubstring('') == 0
    assert s.lengthOfLongestSubstring('abcabcbb') == 3
    assert s.lengthOfLongestSubstring('bbbbb') == 1
    assert s.lengthOfLongestSubstring('abcdefgh') == 8
    assert s.lengthOfLongestSubstring('dvdf') == 3
    assert s.lengthOfLongestSubstring('asjrgapa') == 6
