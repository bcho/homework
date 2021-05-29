from collections import defaultdict


class Solution:

    def longestNiceSubstring(self, s: str) -> str:
        pair_idx = defaultdict(list)
        for idx, c in enumerate(s):
            pair_idx[c].append(idx)

        def find(l, r):
            if r - l + 1 < 2:
                return ''

            for idx, c in enumerate(s[l:r+1]):
                target_c = c.lower()
                if target_c == c:
                    target_c = c.upper()
                has_pair_for_current_character = False
                for p in pair_idx[target_c]:
                    if l <= p <= r:
                        has_pair_for_current_character = True
                        break
                if not has_pair_for_current_character:
                    left, right = find(l, l + idx - 1), find(l + idx + 1, r)
                    if len(left) >= len(right):
                        return left
                    return right
            return s[l:r+1]

        return find(0, len(s) - 1)


if __name__ == '__main__':
    s = Solution()

    assert s.longestNiceSubstring('YazaAay') == 'aAa'
    assert s.longestNiceSubstring('c') == ''
    assert s.longestNiceSubstring('cC') == 'cC'
    assert s.longestNiceSubstring('dDzeE') == 'dD'
