class Solution:
    def spiralOrder(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        if not matrix:
            return []

        n, m = len(matrix), len(matrix[0])
        if n < 2:
            return matrix[0]

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
        rv, visited = [matrix[x][y]], set([(x, y)])
        for dx, dy in dxy():
            while True:
                x, y = x + dx, y + dy
                if in_range(x, y) and (x, y) not in visited:
                    rv.append(matrix[x][y])
                    visited.add((x, y))
                    if len(rv) == n * m:
                        break
                else:
                    x, y = x - dx, y - dy
                    break
            if len(rv) == n * m:
                break

        return rv


s = Solution()

rv = s.spiralOrder([[1]])

print(rv)

rv = s.spiralOrder([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
])

print(rv)

rv = s.spiralOrder([
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
])

print(rv)


rv = s.spiralOrder([
    [6, 9, 7],
])

print(rv)

rv = s.spiralOrder([
    [6, 9, 7],
    [1, 2, 3],
])

print(rv)

rv = s.spiralOrder([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
    [10, 11, 12],
])

print(rv)
