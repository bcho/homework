from typing import List


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        if len(s) < 1:
            return True
        if len(wordDict) < 1:
            return False

        # idea: each time we try to match the suffix of the word, so
        #
        #   f[i] = any(f[i - len(word)]) if word is suffix to s[:i]
        #
        # and we can calculate from the bottom to top

        f = [False] * (len(s) + 1)
        f[0] = True
        for i in range(1, len(s) + 1):
            prefix = s[:i]
            for word in wordDict:
                if not prefix.endswith(word):
                    continue
                f[i] = f[i] or f[i - len(word)]

        return f[len(s)]
