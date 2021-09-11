class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        def is_vowel(c):
            return c in 'aeiou'

        l, r = 0, min(k - 1, len(s) - 1)
        maximum_count = 0
        for c in s[l:r+1]:
            if is_vowel(c):
                maximum_count += 1
        count_of_current_substr = maximum_count
        while True:
            # advance the substring
            if is_vowel(s[l]):
                count_of_current_substr -= 1
            l = l + 1
            r = r + 1
            if r >= len(s):
                return maximum_count
            if is_vowel(s[r]):
                count_of_current_substr += 1
            if count_of_current_substr > maximum_count:
                maximum_count = count_of_current_substr
