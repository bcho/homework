from typing import List


class Solution:
    def checkSubarraySum(self, nums: List[int], k: int) -> bool:
        if len(nums) < 1:
            return False

        # pre-calculate the running sum to reduce from O(n^3) -> O(n^2)
        f = [0] * (len(nums) + 1)
        for idx in range(1, len(nums) + 1):
            f[idx] = f[idx - 1] + nums[idx - 1]

        for ridx in range(len(nums)):
            for lidx in range(ridx):
                # calculate sum(arr[lidx]..arr[ridx])
                # and check if the sum % k == 0
                sub_array_sum = f[ridx + 1] - f[lidx]
                if sub_array_sum == 0 and k == 0:
                    # special case
                    return True
                if k != 0:
                    if sub_array_sum % k == 0:
                        return True

        return False
