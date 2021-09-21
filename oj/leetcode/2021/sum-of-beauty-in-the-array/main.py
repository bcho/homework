class Solution:
    def sumOfBeauties(self, nums: List[int]) -> int:
        F = [nums[0]] * len(nums)
        maximum_f = nums[0]
        i = 1
        while i < len(nums):
            if nums[i] > maximum_f:
                maximum_f = nums[i]
            F[i] = maximum_f
            i = i + 1
        G = [nums[-1]] * len(nums)
        minimum_g = nums[-1]
        i = len(nums) - 2
        while i >= 0:
            if nums[i] < minimum_g:
                minimum_g = nums[i]
            G[i] = minimum_g
            i = i - 1
            
        rv = 0
        i = 1
        while i < len(nums) - 1:
            if F[i - 1] < nums[i] < G[i + 1]:
                rv += 2
            elif nums[i - 1] < nums[i] < nums[i + 1]:
                rv += 1
            i = i + 1
        return rv