class Solution:

    def containsDuplicate(self, nums):
        found = {}
        for num in nums:
            if num in found:
                return False
            found[num] = True
        return True
