from typing import List


class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if len(nums) < 1:
            return 0

        # idea: maintain a shifting window (because all is positive)
        #
        #
        #   a b c d e f
        #   |     |
        #  lidx   ridx
        #
        # if the product in the window is < k, all sub arrays in this window
        # is smaller than k
        #
        # inside the window ([a, d]), there are
        #
        # - a, b, c, d
        # -    b, c, d
        # -       c, d
        # -          d
        #
        # subarrays (ridx - lidx + 1)

        total_count = 0
        lidx, ridx = 0, 0
        window_product = 1
        while True:
            if ridx >= len(nums):
                break
            window_product *= nums[ridx]
            while window_product >= k and lidx <= ridx:
                # adjust the left of the window
                window_product /= nums[lidx]
                lidx += 1
            total_count += ridx - lidx + 1
            # shift the window to right
            ridx += 1
        return total_count
