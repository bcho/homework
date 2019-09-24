from typing import List


class Solution:
    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        if n < 1:
            return []
        if k < 1:
            return []
        if k > n:
            return []

        rv = []

        def dfs(nums_loaded, sum_by_now, num):
            if len(nums_loaded) >= k:
                if sum_by_now == n:
                    rv.append(nums_loaded)
                return
            if num > 9:
                return

            for i in (0, 1):
                # use 0..1 times
                new_sum = num * i + sum_by_now
                if new_sum > n:
                    break
                dfs(nums_loaded + [num] * i, new_sum, num + 1)

        dfs([], 0, 1)
        return rv
