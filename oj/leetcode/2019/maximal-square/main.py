from typing import List


class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        if len(matrix) < 1 or len(matrix[0]) < 1:
            return 0

        rv = 0
        m, n = len(matrix[0]), len(matrix)
        # f0 -> previous row, f1 -> this row
        f0, f1 = [0] * m, [1] * m
        a, b = n - 1, m - 1
        while a >= 0:
            while b >= 0:
                if matrix[a][b] == '0':
                    f1[b] = 0
                elif matrix[a][b] == '1':
                    if b + 1 > m - 1 or a + 1 > n - 1:
                        # corner, maximum squre is 1
                        f1[b] = 1
                    elif (matrix[a][b + 1] != '1'
                          or matrix[a + 1][b] != '1'
                          or matrix[a + 1][b + 1] != '1'):
                        # not a sqaure
                        f1[b] = 1
                    else:
                        # make a new corner
                        f1[b] = min(
                            f1[b + 1], f0[b], f0[b + 1]
                        ) + 1
                    rv = max(f1[b], rv)
                b = b - 1
            f0, f1 = f1[:], [0] * m
            a, b = a - 1, m - 1

        return rv * rv
