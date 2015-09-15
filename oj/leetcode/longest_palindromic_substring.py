class Solution:

    def longestPalindrome_stackoverflow(self, s):
        memoize = {}

        def cache(f):
            def wrapper(*args):
                if args in memoize:
                    return memoize[args]
                rv = f(*args)
                memoize[args] = rv

                return rv
            return wrapper

        @cache
        def cal(a, b):
            if a == b:
                return 1
            if a + 1 == b:
                return 2 if s[a] == s[b] else 1

            nested = cal(a + 1, b - 1)
            if s[a] == s[b]:
                nested = nested + 2
            return nested

        for i in range(len(s)):
            cal(0, i)

        ma, mb, mv = None, None, - 2 << 20
        for (a, b), v in memoize.items():
            if v > mv:
                mv = v
                ma, mb = a, b

        return s[ma:(mb - ma) + 1]

    def longestPalindrome2(self, s):
        len_s = len(s)
        print(len_s)

        f = [[None for i in range(len_s)] for i in range(len_s)]
        maxi, maxj, maxl = None, None, - 2 << 20
        for i in range(len_s - 1, -1, -1):
            for j in range(i, len_s):
                if f[i][j] is not None:
                    continue
                if i == j:
                    f[i][j] = 1
                elif i + 1 == j:
                    f[i][j] = 2 if s[i] == s[j] else 0
                else:
                    f[i][j] = f[i + 1][j - 1]
                    if s[i] == s[j]:
                        f[i][j] = f[i][j] + 2
                    else:
                        f[i][j] = -2 << 10
                # f[j][i] = f[i][j]

                if f[i][j] > maxl:
                    maxi, maxj, maxl = i, j, f[i][j]

        return s[maxi:maxj + 1]

    def longestPalindrome(self, s):
        ma, mb, ml = -1, -1, -1

        def f(a, b):
            while True:
                if a < 0 or b > len(s) - 1 or s[a] != s[b]:
                    break
                a = a - 1
                b = b + 1
            return a + 1, b - 1, b - a + 1

        for i in range(len(s)):
            if i == 0:
                continue
            if i == len(s) - 1:
                break

            a, b, l = f(i, i)
            if l > ml:
                ma, mb, ml = a, b, l
            a, b, l = f(i, i + 1)
            if l > ml:
                ma, mb, ml = a, b, l

        return s[ma:mb + 1]


if __name__ == '__main__':
    s = Solution()
    p = 'abccba'
    # print('o', s.longestPalindrome_stackoverflow(p))
    print('n', s.longestPalindrome(p))
    print(s.longestPalindrome('iopsajhffgvrnyitusobwcxgwlwniqchfnssqttdrnqqcsrigjsxkzcmuoiyxzerakhmexuyeuhjfobrmkoqdljrlojjjysfdslyvckxhuleagmxnzvikfitmkfhevfesnwltekstsueefbrddxrmxokpaxsenwlgytdaexgfwtneurhxvjvpsliepgvspdchmhggybwupiqaqlhjjrildjuewkdxbcpsbjtsevkppvgilrlspejqvzpfeorjmrbdppovvpzxcytscycgwsbnmspihzldjdgilnrlmhaswqaqbecmaocesnpqaotamwofyyfsbmxidowusogmylhlhxftnrmhtnnljjhhcfvywsqimqxqobfsageysonuoagmmviozeouutsiecitrmkypwknorjjiaasxfhsftypspwhvqovmwkjuehujofiabznpipidhfxpoustquzyfurkcgmioxacleqdxgrxbldcuxzgbcazgfismcgmgtjuwchymkzoiqhzaqrtiykdkydgvuaqkllbsactntexcybbjaxlfhyvbxieelstduqzfkoceqzgncvexklahxjnvtyqcjtbfanzgpdmucjlqpiolklmjxnscjcyiybdkgitxnuvtmoypcdldrvalxcxalpwumfx'))  # noqa
    print(s.longestPalindrome("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"))  # noqa
