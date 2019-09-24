from typing import List


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if len(digits) < 1:
            return []

        digit_characters = {
            '2': 'abc',
            '3': 'def',
            '4': 'ghi',
            '5': 'jkl',
            '6': 'mno',
            '7': 'pqrs',
            '8': 'tuv',
            '9': 'wxyz',
        }

        rv = []

        def dfs(loaded, digits):
            if len(digits) < 1:
                rv.append(loaded)
                return

            d, digits = digits[0], digits[1:]
            for c in digit_characters[d]:
                dfs(loaded + c, digits)

        dfs('', digits)
        return rv
