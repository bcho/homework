class Solution:

    def miniumTotal(self, triangle):

        def c(level, row, n):
            if level >= n:
                return 0
            if (level, row) in c.memo:
                return c.memo[(level, row)]

            cost = 0
            cost += min(c(level + 1, row, n), c(level + 1, row + 1, n))
            cost += triangle[level][row]

            c.memo[(level, row)] = cost
            return cost
        c.memo = {}

        return c(0, 0, len(triangle)) if triangle and triangle[0] else 0


if __name__ == '__main__':
    s = Solution()
    print(s.miniumTotal([]))
