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
