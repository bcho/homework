from typing import List


class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        if len(nums) < 4:
            return []

        nums.sort()

        rv = []
        aidx = 0
        while aidx < len(nums) - 3:
            a = nums[aidx]
            bidx = aidx + 1
            while bidx < len(nums) - 2:
                b = nums[bidx]
                cd_target = target - (a + b)
                cidx, didx = bidx + 1, len(nums) - 1
                while cidx < didx:
                    c, d = nums[cidx], nums[didx]
                    increase_cidx, decrease_didx = False, False
                    cd = c + d
                    if cd == cd_target:
                        rv.append([a, b, c, d])
                        increase_cidx = True
                        decrease_didx = True
                    else:
                        increase_cidx = cd < cd_target
                        decrease_didx = cd > cd_target
                    if increase_cidx:
                        while cidx <= didx and nums[cidx] == c:
                            cidx += 1
                    if decrease_didx:
                        while didx >= cidx and nums[didx] == d:
                            didx -= 1

                while bidx <= len(nums) - 2 and nums[bidx] == b:
                    bidx += 1

            while aidx <= len(nums) - 3 and nums[aidx] == a:
                aidx += 1

        return rv
