class Solution:
    def minCharacters(self, a: str, b: str) -> int:
        # matches cond. 1 & 2
        # idea:
        #  - we should be able to find a character X that meet the requirements:
        #      i. for every character C in a, C < X
        #      ii. for every character C in b, C >= X
        #  - we look for the charachter X that requires the least (swap) operations
        #  - cond. 1 & 2 are symmetry -> count in 1 pass
        def case_1(x: str, y: str) -> int:
            minimum_required_opreations_a = len(a) + len(b)
            minimum_required_opreations_b = len(a) + len(b)
            for goal_c in range(1, 26):
                required_operaetions_a = 0
                required_operaetions_b = 0
                for c in x:
                    ord_c = ord(c) - ord('a')
                    if ord_c >= goal_c:
                        required_operaetions_a += 1
                    if ord_c < goal_c:
                        required_operaetions_b += 1
                for c in y:
                    ord_c = ord(c) - ord('a')
                    if ord_c < goal_c:
                        required_operaetions_a += 1
                    if ord_c >= goal_c:
                        required_operaetions_b += 1
                if required_operaetions_a < minimum_required_opreations_a:
                    minimum_required_opreations_a = required_operaetions_a
                if required_operaetions_b < minimum_required_opreations_b:
                    minimum_required_opreations_b = required_operaetions_b

            return min(minimum_required_opreations_a, minimum_required_opreations_b)

        # matches cond. 3
        # idea:
        #  - look for the most common character X in a and b
        #  - swap other characters to it
        def case_3(x: str, y: str) -> int:
            char_counter = [0] * 26
            for c in x:
                char_counter[ord(c) - ord('a')] += 1
            for c in y:
                char_counter[ord(c) - ord('a')] += 1
            most_common_char_count = 0
            for c in char_counter:
                if c > most_common_char_count:
                    most_common_char_count = c

            return len(x) + len(y) - most_common_char_count

        return min(case_1(a, b), case_3(a, b))


if __name__ == '__main__':
    s = Solution()
    assert s.minCharacters('aba', 'caa') == 2
    assert s.minCharacters('dabadd', 'cba') == 3
    assert s.minCharacters('bcb', 'c') == 1
    assert s.minCharacters('a', 'a') == 0
    assert s.minCharacters('acac', 'bd') == 1
    assert s.minCharacters('ace', 'abe') == 2