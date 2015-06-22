class Solution:

    def romanToInt(self, s):

        patterns = {
            'I': 1,
            'IV': 4,
            'V': 5,
            'IX': 9,
            'X': 10,
            'XL': 40,
            'L': 50,
            'XC': 90,
            'C': 100,
            'CD': 400,
            'D': 500,
            'CM': 900,
            'M': 1000
        }

        def match(s):
            ordered_patterns = (
                'IV', 'IX', 'XL', 'XC', 'CD', 'CM',
                'I', 'V', 'X', 'L', 'C', 'D', 'M'
            )
            for pattern in ordered_patterns:
                if s.startswith(pattern):
                    return pattern, patterns[pattern]

        s = s.upper()
        rv = 0
        while True:
            if not s:
                break
            pattern, decimal = match(s)
            rv = rv + decimal
            s = s[len(pattern):]

        return rv


if __name__ == '__main__':
    s = Solution()

    assert 1 == s.romanToInt('I')
    assert 4 == s.romanToInt('IV')
    assert 5 == s.romanToInt('V')
    assert 9 == s.romanToInt('IX')
    assert 10 == s.romanToInt('X')
    assert 40 == s.romanToInt('XL')
    assert 50 == s.romanToInt('L')
    assert 90 == s.romanToInt('XC')
    assert 100 == s.romanToInt('C')
    assert 400 == s.romanToInt('CD')
    assert 500 == s.romanToInt('D')
    assert 900 == s.romanToInt('CM')
    assert 1000 == s.romanToInt('M')

    assert 36 == s.romanToInt('XXXVI')
    assert 2012 == s.romanToInt('MMXII')
    assert 1996 == s.romanToInt('MCMXCVI')
