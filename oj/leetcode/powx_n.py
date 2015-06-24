class Solution:

    def myPow(self, x, n):

        def p(x, n):
            if n == 0:
                return 1
            if n == 1:
                return x
            pow_half_n = p(x, n / 2)
            rv = pow_half_n * pow_half_n
            if n % 2 == 1:
                rv = rv * x
            return rv

        pow_n = p(x, abs(n))
        if n < 0:
            pow_n = 1 / pow_n
        return pow_n
