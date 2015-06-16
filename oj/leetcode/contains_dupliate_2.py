class Solution:

    def containsDuplicate(self, nums, k):
        found = {}
        for i, num in enumerate(nums):
            if num in found and i - found[num] <= k:
                return True
            found[num] = i
        return False
