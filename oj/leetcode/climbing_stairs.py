class Solution:

    def climbStairs(self, n):

        def f(l):
            if l in f.memo:
                return f.memo[l]

            count = 0
            count += f(l - 2) if l >= 2 else 0
            count += f(l - 1) if l >= 1 else 0

            f.memo[l] = count
            return count

        f.memo = {
            0: 1,
            1: 1
        }

        return f(n)


if __name__ == '__main__':
    s = Solution()

    print(s.climbStairs(1))
    print(s.climbStairs(2))
    print(s.climbStairs(5))
