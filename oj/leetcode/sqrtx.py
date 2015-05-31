class Solution:

    def mySqrt(self, x):
        if x < 2:
            return x

        eps = 0.1
        xi = float(x)
        while True:
            xi2 = xi ** 2
            if abs(xi2 - x) <= eps:
                return int(round(xi))
            xi = xi - (xi ** 2 - x) / (2 * xi)


if __name__ == '__main__':
    s = Solution()

    for i in range(100001):
        ex = int(round(i ** 0.5))
        ax = s.mySqrt(i)
        print(i, ex, ax)
        assert ex == ax
