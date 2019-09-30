from typing import List


class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        if len(nums) < 2:
            return 0
        sum_nums = sum(nums)
        if sum_nums % 2 == 1:
            # sum must be even
            return False

        # So now we change the problem to 0/1 knapsack:
        #
        # the capacity is target, we want to fill the knapsack with nums
        target = sum_nums // 2
        f0 = [0] * (target + 1)
        # we can always fill the 0 capacity knapsack
        f0[0] = 1
        f1 = [0] * (target + 1)
        for idx, num in enumerate(nums):
            for t in range(1, target + 1):
                f1[t] = f0[t]
                if t >= num:
                    # try to fill the knapsack
                    f1[t] = max(f1[t], f0[t - num])
            f0, f1 = f1[:], [0] * (target + 1)
            if f0[target] > 0:
                return True
        return False
