from typing import List


class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        from collections import deque

        if len(nums) < 1:
            return []
        if k < 1:
            return []

        # hold the index of the item in the window
        #
        # invariant: each item in the left is larger or equal
        # to the value in the right
        window = deque()

        rv = []
        for idx, num in enumerate(nums):
            while len(window) > 0 and window[0] <= idx - k:
                # shfit the window to right
                # discard all items that not in the window
                window.popleft()
            while len(window) > 0 and nums[window[-1]] <= num:
                # discard the item that smaller than the new arrivial
                # NOTE: this loop is O(k), but I think the average case is O(1)
                window.pop()
            window.append(idx)
            if idx >= k - 1:
                rv.append(nums[window[0]])

        return rv


if __name__ == '__main__':
    s = Solution()
    assert s.maxSlidingWindow([1, 2, 3], 1) == [1, 2, 3]
    assert s.maxSlidingWindow([1, 3, -1, -1, -1, 2], 3) == [3, 3, -1, 2]
    assert s.maxSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3) == [
        3, 3, 5, 5, 6, 7,
    ]
