from typing import List


class Solution:

    def canJump(self, nums: List[int]) -> bool:
        # simple cases
        if len(nums) < 1:
            return False
        if len(nums) == 1:
            return True

        # distance_can_jump -> record the farthest can jump by now (step=0)
        distance_can_jump = nums[0]
        # check each step in [0 .. size - 2], see how far
        # can jump from each step
        for i in range(len(nums) - 1):
            if i > distance_can_jump:
                # cannot reach this step from last step, break
                # this gurantees that:
                # if len(nums)-1-1 cannot reach to len(nums)-1,
                # any steps before len(nums)-1-1 will not reach to len(nums)-1
                break

            distance_can_jump = max(
                distance_can_jump,
                # the farthest in can jump from this step,
                # the smallest possible distance for step=i is `i`
                nums[i] + i,
            )

        # check if can jump to the last index
        return distance_can_jump >= len(nums) - 1


if __name__ == '__main__':
    s = Solution()
    assert s.canJump([2, 3, 1, 1, 4])
    assert not s.canJump([3, 2, 1, 0, 4])
    assert not s.canJump([3, 2, 1, 0, 0, 4])
    assert s.canJump([2, 3, 0, 1, 4])
    assert not s.canJump([0, 2, 3])
