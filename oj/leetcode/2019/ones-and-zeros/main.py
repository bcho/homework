from typing import List


class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        if len(strs) < 1:
            return 0
        if m == 0 and n == 0:
            return 0

        strs_zero, strs_one = {}, {}
        for s in strs:
            strs_zero[s], strs_one[s] = 0, 0
            for c in s:
                if c == '0':
                    strs_zero[s] += 1
                if c == '1':
                    strs_one[s] += 1

        # idea: f[M, N] = max(f[M, N], f[M - ones, N - zeros] + 1)

        f = [
            [0 for one in range(n + 1)]
            for zero in range(m + 1)
        ]
        for s in strs:
            s_zero, s_one = strs_zero[s], strs_one[s]
            # NOTE: each item can be used at most one time, so calculate from
            # bottom right (avoid over-counting)
            for zero in range(m, s_zero - 1, -1):
                for one in range(n, s_one - 1, -1):
                    f[zero][one] = max(
                        f[zero][one],
                        f[zero - s_zero][one - s_one] + 1
                    )

        return f[m][n]
