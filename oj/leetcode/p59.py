class Solution:
    def generateMatrix(self, n):
        if n < 1:
            return []

        m = n

        def dxy():
            while True:
                yield 0, 1
                yield 1, 0
                yield 0, -1
                yield -1, 0

        def in_range(x, y):
            if x < 0 or y < 0 or x >= n or y >= m:
                return False
            return True

        x, y = 0, 0
        rv, visited = [[1] * n for i in range(n)], set([(x, y)])
        for dx, dy in dxy():
            while True:
                x, y = x + dx, y + dy
                if in_range(x, y) and (x, y) not in visited:
                    rv[x][y] = len(visited) + 1
                    visited.add((x, y))
                    if len(visited) == n * m:
                        break
                else:
                    x, y = x - dx, y - dy
                    break
            if len(visited) == n * m:
                break

        return rv


s = Solution()

print(s.generateMatrix(3))
print(s.generateMatrix(4))
