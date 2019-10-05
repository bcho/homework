from typing import List


class Solution:

    def longestOnes(self, A, K):
        # idea: maintain a window that: the count of zeros inside <= K
        left_idx, right_idx = 0, 0
        zeros_in_window, max_size = 0, 0
        while right_idx < len(A):
            if A[right_idx] == 0:
                # count new zero
                zeros_in_window += 1
            while zeros_in_window > K:
                # zero exceeded, shrink the window from left
                if A[left_idx] == 0:
                    zeros_in_window -= 1
                left_idx += 1
            # the invariant is hold for current wnidow,
            # calculate current window's size
            max_size = max(max_size, right_idx - left_idx + 1)

            # try shift the window right
            right_idx = right_idx + 1

        return max_size

    def longestOnes_dp_tle(self, A: List[int], K: int) -> int:
        if len(A) < 1:
            return 0

        longest = 0
        f_prev, f_cur = [0] * len(A), [0] * len(A)
        for idx, num in enumerate(A):
            if num == 1:
                f_prev[idx] = 1
                if idx > 0:
                    f_prev[idx] += f_prev[idx - 1]
                if longest < f_prev[idx]:
                    longest = f_prev[idx]
            else:
                f_prev[idx] = 0
        for k in range(K):
            for idx, num in enumerate(A):
                if num == 1:
                    f_cur[idx] = 1
                    if idx > 0:
                        f_cur[idx] += f_cur[idx - 1]
                elif num == 0:
                    f_cur[idx] = 1
                    if idx > 0:
                        f_cur[idx] = max(
                            1,
                            f_prev[idx - 1] + 1
                        )
                if longest < f_cur[idx]:
                    longest = f_cur[idx]
                if longest >= len(A):
                    return longest
            f_prev, f_cur = f_cur[:], [0] * len(A)

        return longest
