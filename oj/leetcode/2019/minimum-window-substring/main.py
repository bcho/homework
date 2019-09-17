class Solution:

    def minWindow(self, s: str, t: str) -> str:
        # base cases
        if len(t) > len(s):
            return ''
        if len(s) == 0:
            return ''
        if len(t) == 0:
            return ''

        matched_counter = {}
        expected_counter = {}
        for c in t:
            if c not in expected_counter:
                expected_counter[c] = 0
            expected_counter[c] += 1
            matched_counter[c] = 0

        def is_matched(current_counter):
            for c, expected_count in expected_counter.items():
                if current_counter.get(c, 0) < expected_count:
                    return False
            return True

        min_sub_string = None
        lidx, ridx = 0, -1

        def advance_r_pointer():
            nonlocal ridx
            if ridx >= len(s) - 1:
                # already reached end
                return False
            ridx += 1
            c = s[ridx]
            if c in t:
                matched_counter[c] += 1
            return True

        def advance_l_pointer():
            nonlocal lidx
            no_longer_matched = False
            if lidx >= len(s) - 1:
                # already reached end
                return no_longer_matched
            if lidx >= ridx:
                # cannot advance
                return no_longer_matched
            if s[lidx] in t:
                c = s[lidx]
                matched_counter[c] -= 1
                no_longer_matched = matched_counter[c] < expected_counter[c]

            lidx += 1
            return no_longer_matched

        def update_min_sub_string(l, r):
            nonlocal min_sub_string
            if min_sub_string == '' or r - l + 1 < len(min_sub_string):
                min_sub_string = s[l:r+1]

        min_sub_string = ''
        while True:
            if lidx == ridx == len(s) - 1:
                break
            while True:
                if ridx >= len(s) - 1:
                    if not is_matched(matched_counter):
                        # fast track: no longer match, should have find
                        # the minimum sub string
                        return min_sub_string
                advance_r_pointer()
                if is_matched(matched_counter):
                    # found new matched, try to shrink the window
                    update_min_sub_string(lidx, ridx)
                    break
            while True:
                update_min_sub_string(lidx, ridx)
                if lidx >= ridx:
                    return min_sub_string
                no_longer_matched = advance_l_pointer()
                if not no_longer_matched:
                    # still match, keep shrinking
                    continue
                # no longer match, stop shrinking
                break

        return min_sub_string


if __name__ == '__main__':
    s = Solution()
    assert s.minWindow('ab', 'b') == 'b'
    assert s.minWindow('a', 'a') == 'a'
    assert s.minWindow('ADOBECODEBANC', 'ABC') == 'BANC'
    assert s.minWindow('ADOBECODEBAC', 'ABC') == 'BAC'
    assert s.minWindow('ADDDD', 'ABC') == ''
    assert s.minWindow('ab', 'a') == 'a'
