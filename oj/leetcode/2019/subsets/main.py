from typinig import List


class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        if len(nums) < 1:
            return [[]]

        rv = []

        def dfs(loaded, items):
            if len(items) < 1:
                rv.append(loaded)
                return

            dfs(loaded + items[0:1], items[1:])
            dfs(loaded, items[1:])

        dfs([], nums)

        return rv
