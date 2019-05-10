class Solution_tle:

    def isMatch(self, s: str, p: str) -> bool:
        p = self.normalize_pattern(p)

        # aabcd ~= aabc* => d ~= *
        i = 0
        while True:
            if i >= len(p) or i >= len(s):
                break
            if p[i] not in (s[i], '?'):
                break
            i = i + 1
        p, s = p[i:], s[i:]

        # abcd ~= *bcd => a ~= *
        i, j = len(p) - 1, len(s) - 1
        while True:
            if i < 0 or j < 0:
                break
            if p[i] not in (s[j], '?'):
                break
            i, j = i - 1, j - 1
        p, s = p[:i+1], s[:j+1]

        return self.sub_match(s, self.normalize_pattern(p))

    def normalize_pattern(self, p: str) -> str:
        x = ''
        for i in p:
            if x and x[-1] == '*' and i == '*':
                # skip consecutive *
                continue
            x = x + i
        return x

    def minimum_match_size(self, p: str) -> str:
        return sum(1 for i in p if i not in '*?')

    def sub_match(self, s: str, p: str) -> bool:
        if s == '' and p == '':
            # already done
            return True
        if p == '':
            # have more s to match
            return False
        if s == '':
            if p == '*':
                return True
            # have more p to match
            return False

        if p[-1] not in '*?' and p[-1] != s[-1]:
            # abc ~= *bd
            return False

        if p[0] == '*':
            p_next = p[1:]
            s_offset = len(s) - self.minimum_match_size(p_next)
            s_next = s
            while True:
                if s_offset < 0:
                    return False
                s_next = s[s_offset:]
                if self.sub_match(s_next, p_next):
                    # found a match
                    return True
                s_offset = s_offset - 1  # advance with *
            return False
        elif p[0] == '?':
            # abc ~= ?bc
            return self.sub_match(s[1:], p[1:])
        elif p[0] == s[0]:
            # abc ~= abc
            return self.sub_match(s[1:], p[1:])

        # non match
        return False


# NOTE: Avoid handling *, because more stars means the more sub trees to search
# with. Remove all the stars and check for the required sub strings only, so we
# can restrict the complexity with the same scale of the p & s.
class Solution:

    def normalize_pattern(self, p: str) -> str:
        x = ''
        for i in p:
            if x and x[-1] == '*' and i == '*':
                # skip consecutive *
                continue
            x = x + i
        return x

    def is_sub_matched(self, s: str, p: str) -> bool:
        for sc, pc in zip(s, p):
            if pc not in (sc, '?'):
                # not match
                return False
        return True

    def isMatch(self, s: str, p: str) -> bool:
        p = self.normalize_pattern(p)

        # aabcd ~= aabc* => d ~= *
        i = 0
        while True:
            if i >= len(p) or i >= len(s):
                break
            if p[i] == '*':
                # found wildcard, start matching
                break
            if p[i] not in (s[i], '?'):
                # prefix mismatch
                return False
            i = i + 1
        p, s = p[i:], s[i:]

        # abcd ~= *bcd => a ~= *
        i, j = len(p) - 1, len(s) - 1
        while True:
            if i < 0 or j < 0:
                break
            if p[i] == '*':
                # found wildcard, start matching
                break
            if p[i] not in (s[j], '?'):
                # suffix mismatch
                return False
            i, j = i - 1, j - 1
        p, s = p[:i+1], s[:j+1]

        if p == '' and s == '':
            # already done
            return True
        if p == '':
            # have more s to match
            return False
        if s == '':
            if p == '*':
                return True
            # have more p to match
            return False

        for part_to_match in p.split('*'):
            found_matched_sub_part = False
            for i in range(len(s) - len(part_to_match) + 1):
                s_to_match = s[i:i+len(part_to_match)]
                if self.is_sub_matched(s_to_match, part_to_match):
                    found_matched_sub_part = True
                    s = s[i+len(part_to_match):]
                    break
            if not found_matched_sub_part:
                # no suit for this sub part
                return False
        return True


if __name__ == '__main__':
    ss = Solution()

    for (s, p), e in [
        (('a', '*a*'), True),
        (('babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb',
         'b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a'),
         False),
        (('babbbbaabababaabbababaababaabbaabababbaaababbababaaaaaabbabaaaabababbabbababbbaaaababbbabbbbbbbbbbaabbb',
         'b**bb**a**bba*b**a*bbb**aba***babbb*aa****aabb*bbb***a*'),
         False),
        (('aaabbbaabaaaabbbbbbaaabafadbaadfadfbaa', 'a******b'), False),
        (('aaabbbaabaaaabbbbbbaaabafadbaadfadfbaab', 'a******b'), True),
        (('', '*'), True),
        (('x', '?'), True),
        (('', '?'), False),
        (('c', '*?*'), True),
        (('acdcb', 'a*c?b'), False),
        (('acdcb', 'a*cb'), True),
        (('ho', 'ho**'), True),
        (('aa', 'a'), False),
        (('aa', '*'), True),
        (('cb', '?a'), False),
        (('adceb', '*a*b'), True),
        (('aaa', '??a'), True),
        (('aaa', '?a'), False),
        (('aaa', '*?a'), True),
        (('aaa', '**?a'), True),
        (('aaa' * 1000, '**?a'), True),
    ]:
        print(s, p)
        assert ss.isMatch(s, p) == e

    print('all done')
