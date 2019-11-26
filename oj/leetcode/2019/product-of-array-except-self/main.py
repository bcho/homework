from typing import List


class Solution:

    def productExceptSelf(self, nums: List[int]) -> List[int]:
        # rv[i] = rv[0..i] * rv[i+1..n]
        rv = [1] * len(nums)
        # first forward pass: calculate rv[0..i]
        for idx, num in enumerate(nums[:-1]):
            rv[idx + 1] = rv[idx] * num
        d = nums[-1]
        # second backward pass: calculate rv[i+1..n]
        for idx in range(len(nums) - 2, -1, -1):
            rv[idx] *= d
            d *= nums[idx]

        return rv
