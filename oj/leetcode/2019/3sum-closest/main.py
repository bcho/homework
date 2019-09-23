from typing import List


class Solution:

    def threeSumClosest(self, nums: List[int], target: int) -> int:
        if len(nums) < 1:
            return -1
        if len(nums) == 1:
            return nums[0]

        rv, min_delta = float('inf'), float('inf')
        nums.sort()
        for aidx, a in enumerate(nums):
            bidx, cidx = aidx + 1, len(nums) - 1
            while bidx < cidx:
                b = nums[bidx]
                c = nums[cidx]
                s = a + b + c
                delta = s - target
                if abs(delta) < min_delta:
                    min_delta = abs(delta)
                    rv = s
                if delta > 0:
                    cidx -= 1
                elif delta < 0:
                    bidx += 1
                else:
                    # found the target, just return it
                    return target

        return rv


if __name__ == '__main__':
    s = Solution()
    assert s.threeSumClosest([-1, 2, 1, -4], 1) == 2
    assert s.threeSumClosest([-1, 2, 1, -4], 4) == 2
    assert s.threeSumClosest([-1, 2, 1, -4], -3) == -3
