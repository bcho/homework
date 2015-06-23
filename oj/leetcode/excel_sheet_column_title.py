class Solution:

    def convertToTitle(self, n):
        encodings = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
        digit_to_char = lambda x: encodings[x]

        rv = []
        while True:
            if n == 0:
                break
            r = n % 26
            if r == 0:
                n = n - 26
                r = 26
            n = n / 26
            rv.append(digit_to_char(r))

        return ''.join(i for i in rv if i != ' ')[::-1]


if __name__ == '__main__':
    s = Solution()

    a = s.convertToTitle(1)
    assert 'A' == a

    a = s.convertToTitle(2)
    assert 'B' == a

    a = s.convertToTitle(26 ** 2 + 26)
    assert 'ZZ' == a

    a = s.convertToTitle(26)
    assert 'Z' == a

    a = s.convertToTitle(27)
    assert 'AA' == a

    a = s.convertToTitle(28)
    assert 'AB' == a

    a = s.convertToTitle(29)
    assert 'AC' == a
