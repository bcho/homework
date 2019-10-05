from typing import List


class Solution:
    def sortColors_two_pointers(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        def swap(a, b, upper_bound):
            i, j = a, b
            while i <= j:
                while nums[i] <= upper_bound:
                    i = i + 1
                    if i > j:
                        break
                if i > j:
                    break
                if nums[i] > upper_bound:
                    nums[i], nums[j] = nums[j], nums[i]
                    j = j - 1

            # j is the boundary index for value <= upper_bound
            return j

        last_j = swap(0, len(nums) - 1, 1)
        swap(0, last_j, 0)

    def sortColors_one_pass(self, nums: List[int]) -> None:
        p0, p1, p2 = 0, 0, len(nums) - 1
        while p1 <= p2:
            if nums[p1] == 0 and p0 != p1:
                # current value is zero, swap with zero section
                nums[p0], nums[p1] = nums[p1], nums[p0]
                p0 += 1
            elif nums[p1] == 2 and p0 != p2:
                # current value is two, swap with two section
                nums[p1], nums[p2] = nums[p2], nums[p1]
                p2 -= 1
            else:  # nums[p1] == 1
                p1 += 1
