from typing import List


class Solution:
    def partition(self, s: str) -> List[List[str]]:
        if len(s) < 1:
            return []

        def is_palindrome(s):
            if len(s) < 2:
                return True
            return s[0] == s[-1] and is_palindrome(s[1:-1])

        rv = []

        def dfs(parts, remaining):
            if len(remaining) < 1:
                matched = True
                for p in parts[::-1]:
                    if not is_palindrome(p):
                        matched = False
                        break
                if matched:
                    rv.append(parts)
                return

            new_remaining = remaining[1:]
            if len(parts) > 0:
                # [0, 1, ... n]
                # for parts before n, they are palindrome
                if is_palindrome(parts[-1]):
                    # if n is palindrome, push new string with only
                    # one character
                    dfs(parts + [remaining[0]], new_remaining)
                new_string = parts[-1] + remaining[0]
                # append the charater to n, see if we can find a palindrome
                # in the future
                dfs(parts[:-1] + [new_string], new_remaining)
            else:
                # use only one character
                dfs(parts + [remaining[0]], new_remaining)

        dfs([], s)
        return rv
