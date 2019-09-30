from typing import List


class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        if len(matrix) < 1:
            return 0

        heights = [0] * len(matrix[0])
        left_most_zero = [-1] * len(matrix[0])
        right_most_zero = [len(matrix[0])] * len(matrix[0])
        max_area = 0

        # basic idea:
        #
        # scan for the top row, and calculate the maximum rectangle in that row
        #
        # one row:
        #
        #       1 0 1 1 0
        # for idx = 0, the maximum rectangle is w=1, h=1
        # for idx = 2, the maximum rectangle is w=2, h=1
        # for idx = 3, the maximum rectangle is w=2, h=1
        #
        # two row:
        #
        #
        #       1 0 1 1 0
        #       0 0 0 1 0
        #
        # for idx = 0, the maximum rectangle is w=0, h=0
        # for idx = 3, the maximum rectangle is w=1, h=2
        #
        # the w is defined by:
        #
        # - the last index of 0 in the left
        # - the first index of 0 in the right
        #
        #
        # the h is defined by:
        #
        # - if the value is '1', the height is last_row_height + 1, otherwise 0
        for row_value in matrix:
            for col, value in enumerate(row_value):
                # calculate the accumulate height in this row
                if value == '1':
                    heights[col] = heights[col] + 1
                else:
                    heights[col] = 0

            last_zero_idx = -1
            for col, value in enumerate(row_value):
                if value == '1':
                    # find the last zero in the left
                    left_most_zero[col] = max(
                        last_zero_idx,
                        left_most_zero[col]
                    )
                else:
                    # mark this index as last zero in the left
                    last_zero_idx = col
                    left_most_zero[col] = -1

            last_zero_idx = len(row_value)
            for col in range(len(row_value)-1, -1, -1):
                value = row_value[col]
                if value == '1':
                    # find the first zero in the right
                    right_most_zero[col] = min(
                        last_zero_idx,
                        right_most_zero[col]
                    )
                else:
                    # mark this index as first zero in the right
                    last_zero_idx = col
                    right_most_zero[col] = len(row_value)

            for height, left_zero_idx, right_zero_idx in zip(
                heights,
                left_most_zero,
                right_most_zero
            ):
                # calculate the rectangles in this row
                width = right_zero_idx - left_zero_idx - 1
                area = width * height
                if area > max_area:
                    max_area = area

        return max_area
