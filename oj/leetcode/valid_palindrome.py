class Solution:

    def isPalindrome(self, s):

        is_alphanum = lambda x: 'a' <= x.lower() <= 'z' or '0' <= x <= '9'
        take_only_alphanum = lambda x: ''.join(filter(is_alphanum, x)).lower()

        return take_only_alphanum(s) == take_only_alphanum(s[::-1])


if __name__ == '__main__':
    s = Solution()
    assert(s.isPalindrome('abccba'))
    assert(s.isPalindrome('abccbA'))
    assert(not s.isPalindrome('abccbAd'))
    assert(s.isPalindrome('a man, a plan, a canal: Panama'))
    assert(not s.isPalindrome('race a car'))
