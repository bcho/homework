class Solution:

    def intToRoman(self, num):

        letters = (
            ('M', 1000),
            ('CM', 900),
            ('D', 500),
            ('CD', 400),
            ('C', 100),
            ('XC', 90),
            ('L', 50),
            ('XL', 40),
            ('X', 10),
            ('IX', 9),
            ('V', 5),
            ('IV', 4),
            ('I', 1),
        )

        rv = ''
        for letter, integer in letters:
            while num >= integer:
                rv = rv + letter
                num = num - integer
        return rv


if __name__ == '__main__':
    s = Solution()

    assert 'I' == s.intToRoman(1)
    assert 'IV' == s.intToRoman(4)
    assert 'M' == s.intToRoman(1000)

    assert 'XXXVI' == s.intToRoman(36)
    assert 'MMXII' == s.intToRoman(2012)
    assert 'MCMXCVI' == s.intToRoman(1996)
