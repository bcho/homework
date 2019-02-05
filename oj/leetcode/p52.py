class Solution:
    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """
        if n < 1:
            return []

        def check_cross(q, qs):
            for dx, dy in [(1, 1), (1, -1), (-1, 1), (-1, -1)]:
                x, y = q
                while True:
                    x, y = x + dx, y + dy
                    if x >= n or x < 0 or y >= n or y < 0:
                        break
                    if (x, y) in qs:
                        return False
            return True

        rv = 0

        def perm(qs, ds):
            nonlocal rv
            if len(qs) == n:
                for q in qs:
                    if not check_cross(q, qs):
                        return
                rv = rv + 1
                return
            # TODO: 镜像剪枝
            for idx, d in enumerate(ds):
                q = (d, n - len(ds))
                qs.add(q)
                perm(qs, ds[:idx] + ds[idx+1:])
                qs.remove(q)

        perm(set(), [i for i in range(n)])

        return rv


s = Solution()

print(s.solveNQueens(1))
print(s.solveNQueens(2))
print(s.solveNQueens(3))
print(s.solveNQueens(4))
print(s.solveNQueens(5))
print(s.solveNQueens(8))
