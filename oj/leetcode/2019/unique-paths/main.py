class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        if m < 1 or n < 1:
            return 0
        f0, f1 = [0] * m, [0] * m
        for i in range(n):
            for j in range(m):
                if i == 0:
                    f1[j] = 1
                elif j == 0:
                    f1[j] = 1
                else:
                    # from left and top
                    f1[j] = f1[j - 1] + f0[j]
            f0, f1 = f1[:], [0] * m
        return f0[m - 1]
