class Solution:

    def numDecodings(self, s: str) -> int:
        if len(s) < 1:
            return 0

        # f[i] = sum(
        #           f[i-1],  # if s[i] in alphabets
        #           f[i-2]   # if s[i-1:i+1] in alphabets
        #        )
        #
        # special case:
        #
        # if nor s[i] or s[i-1:i+1] in alphabets, return 0

        alphabets = {str(i) for i in range(1, 27)}

        f = [0] * len(s)
        last_c, ss = s[0], s[1:]
        if last_c not in alphabets:
            # unable to decode
            return 0

        f[0] = 1
        for _idx, c in enumerate(ss):
            idx = _idx + 1

            comp_with_last = last_c + c
            if c not in alphabets and comp_with_last not in alphabets:
                # unable to decode
                return 0

            if c in alphabets:
                f[idx] = f[idx - 1]
            if last_c + c in alphabets:
                d = 1
                if idx > 2:
                    # can look forward
                    d = f[idx - 2]
                f[idx] += d
            last_c = c

        return f[len(s) - 1]


if __name__ == '__main__':
    s = Solution()
    assert s.numDecodings('12') == 2
    assert s.numDecodings('226') == 3
    assert s.numDecodings('2222') == 5
    assert s.numDecodings('0') == 0
    assert s.numDecodings('012') == 0
    assert s.numDecodings('10') == 1
    assert s.numDecodings('100') == 0
