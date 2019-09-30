from typing import List


class Solution:
    def canPartitionKSubsets(self, nums: List[int], k: int) -> bool:
        if len(nums) < k:
            return False
        if k < 1:
            return False
        if k == 1:
            return True

        sum_nums = sum(nums)
        if sum_nums % k != 0:
            return False
        target = sum_nums // k

        visited_idx = set()

        def dfs(current_sum, k_needed, from_idx):
            if k_needed == 0:
                # found
                return True
            if current_sum == target:
                # reach target, restart searching from 0
                return dfs(0, k_needed - 1, 0)
            idx = from_idx
            while idx < len(nums):
                if idx in visited_idx:
                    idx = idx + 1
                    continue
                # try to use this item
                visited_idx.add(idx)
                if dfs(current_sum + nums[idx], k_needed, idx + 1):
                    return True
                visited_idx.remove(idx)
                idx = idx + 1
            return False

        return dfs(0, k, 0)
