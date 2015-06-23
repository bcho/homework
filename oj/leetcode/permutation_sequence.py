class Solution:

    def getPermutation(self, n, k):

        def factorial(n):
            rv = 1
            for i in range(1, n + 1):
                rv = rv * i
            return rv

        def g(numbers, n, k):
            n_1_fact = factorial(n - 1)
            digit = numbers.pop((k - 1) / n_1_fact)

            k = k % n_1_fact
            if k == 0:
                k = n_1_fact
            n = n - 1

            if numbers:
                return str(digit) + g(numbers, n, k)
            return str(digit)

        return g([i for i in range(1, n + 1)], n, k)


if __name__ == '__main__':
    s = Solution()

    assert '123' == s.getPermutation(3, 1)
    assert '132' == s.getPermutation(3, 2)
    assert '4321' == s.getPermutation(4, 24)
