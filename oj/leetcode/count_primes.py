class Solution:

    def countPrimes(self, n):
        shieve = [True] * n
        for i in range(2, n):
            if not shieve[i]:
                continue
            num = i + i
            while num < n:
                shieve[num] = False
                num = num + i
        rv = 0
        for i in shieve[2:]:
            if i:
                rv = rv + 1
        return rv


if __name__ == '__main__':
    s = Solution()

    assert 0 == s.countPrimes(1)
    assert 0 == s.countPrimes(2)
    assert 1 == s.countPrimes(3)
    assert 7 == s.countPrimes(19)
    assert 8 == s.countPrimes(20)
