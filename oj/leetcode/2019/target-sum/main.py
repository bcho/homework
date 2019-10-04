from typing import List


class Solution:
    def findTargetSumWays(self, nums: List[int], S: int) -> int:
        if len(nums) < 1:
            return 0
        if len(nums) == 1 and nums[0] == S:
            return 1 if S != 0 else 2

        sum_nums = sum(nums)
        if sum_nums < S:
            return 0

        # sum(positive) - sum(negative) = target
        # sum(positive) + sum(negative) = sum(nums)
        # sum(positive) * 2             = target + sum(nums)
        # target_sum = (target + sum(nums)) / 2

        sum_p_2 = S + sum_nums
        if sum_p_2 % 2 != 0:
            return 0
        sum_p = (S + sum(nums)) // 2

        f = [0] * (sum_p + 1)
        f[0] = 1
        for num in nums:
            for t in range(sum_p, num - 1, -1):
                f[t] += f[t-num]

        return f[sum_p]

    def findTargetSumWays_state(self, nums: List[int], S: int) -> int:
        from collections import defaultdict

        if len(nums) < 1:
            return 0
        if len(nums) == 1 and nums[0] == S:
            return 1 if S != 0 else 2

        # idea: for each item, we can put +/- sign, so this item will affect
        # next item's count. We use f[k, v] to represent the total count
        # for the value v, using item #k, so:
        #
        #   # propagate to next state
        #   f[n + 1, v + a[n]] += f[n]
        #   f[n + 1, v - a[n]] += f[n]

        f = [defaultdict(int) for i in range(len(nums) + 1)]
        f[0][0] = 1
        for idx, num in enumerate(nums):
            for sum_by_far, count in f[idx].items():
                f[idx + 1][sum_by_far + num] += count
                f[idx + 1][sum_by_far - num] += count

        return f[len(nums)][S]
