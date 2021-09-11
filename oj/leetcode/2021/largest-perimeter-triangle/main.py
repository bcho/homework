class Solution:
    def largestPerimeter(self, nums: List[int]) -> int:
        nums = sorted(nums, reverse=True)
        for ia in range(len(nums) - 2):
            ib = ia + 1
            ic = ib + 1
            a, b, c = nums[ia], nums[ib], nums[ic]
            if c + b <= a:
                continue
            return a + b + c
        return 0
