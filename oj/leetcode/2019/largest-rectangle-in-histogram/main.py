from typing import List


class Solution:

    def largestRectangleArea(self, heights: List[int]) -> int:
        # base cases
        if len(heights) < 1:
            return 0
        if len(heights) == 1:
            return heights[0]

        # low_idx maintains the lowest rectangle index for height in idx
        low_idx = [i for i in range(len(heights))]
        # high_idx maintains the highest rectangle index for height in idx
        high_idx = [i for i in range(len(heights))]
        height_stack = []
        for height_idx, height in enumerate(heights):
            while True:
                if len(height_stack) < 1:
                    # empty stack, push to the stack
                    height_stack.append((height, height_idx))
                    break
                max_height_so_far, max_height_idx = height_stack[-1]
                if height >= max_height_so_far:
                    # current height is >= the local maximum height,
                    # add to the stack
                    height_stack.append((height, height_idx))
                    break
                else:
                    # current height is < the local maximum height,
                    # pop the local maximum height
                    height_stack.pop()
                    # update the highest bound for the previous
                    # local maximum height
                    high_idx[max_height_idx] = height_idx - 1
                    # mark the lowest bound for the current height
                    low_idx[height_idx] = low_idx[max_height_idx]

        if len(height_stack) > 0:
            # the stack is not empty, update all remaining items' highest bound
            _, max_height_idx = height_stack[-1]
            for _, height_idx in height_stack:
                high_idx[height_idx] = max_height_idx

        max_area = 0
        for height_idx, height in enumerate(heights):
            min_range_for_height = low_idx[height_idx]
            max_range_for_height = high_idx[height_idx]
            area = height * (max_range_for_height - min_range_for_height + 1)
            if area > max_area:
                max_area = area

        return max_area


if __name__ == '__main__':
    s = Solution()
    assert s.largestRectangleArea([1, 2, 3, 4, 5]) == 9
    assert s.largestRectangleArea([2, 1, 2]) == 3
    assert s.largestRectangleArea([2, 3]) == 4
    assert s.largestRectangleArea([2, 1, 5, 6, 2, 3]) == 10
    assert s.largestRectangleArea([1]) == 1
    assert s.largestRectangleArea([1, 1]) == 2
    assert s.largestRectangleArea([1, 2]) == 2
    assert s.largestRectangleArea([2, 1]) == 2
    assert s.largestRectangleArea([1, 3, 4, 5, 2, 1]) == 9
    assert s.largestRectangleArea([0, 0, 1, 0, 1]) == 1
    assert s.largestRectangleArea([1, 1, 2, 8, 1]) == 8
