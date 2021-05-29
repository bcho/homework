class Solution:
    def minimumLength(self, s: str) -> int:
        while len(s) > 1:
            prefix = s[0]
            for c in s[1:len(s)-1]:
                if c != prefix[0]:
                    break
                prefix += c
                continue
            if len(prefix) == len(s):
                s = ''
                break
            suffix = s[-1]
            if suffix[0] != prefix[0]:
                break
            for suffix_idx in range(len(s) - 2, len(prefix), -1):
                c = s[suffix_idx]
                if c != suffix[0]:
                    break
                suffix += c
                continue
            # print(f's={s}, prefix={prefix} suffix={suffix}')
            s = s[len(prefix):len(s)-len(suffix)]
        # print(s)
        return len(s)


if __name__ == '__main__':
    s = Solution()

    assert s.minimumLength('aabccabba') == 3
    assert s.minimumLength('a') == 1
    assert s.minimumLength('aa') == 0
    assert s.minimumLength('ca') == 2
    assert s.minimumLength("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbacccabbabccaccbacaaccacacccaccbbbacaabbccbbcbcbcacacccccccbcbbabccaacaabacbbaccccbabbcbccccaccacaccbcbbcbcccabaaaabbbbbbbbbbbbbbb") == 109
