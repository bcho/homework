from typing import List


class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        if len(nums) < 1:
            return 0

        # idea: F[t] = sum(F[t - num[i]])
        # so we calculate/sum all possible combinations from 0..target

        f = [0] * (target + 1)
        f[0] = 1
        for t in range(1, target + 1):
            for num in nums:
                if t - num < 0:
                    continue
                f[t] += f[t - num]

        return f[target]
