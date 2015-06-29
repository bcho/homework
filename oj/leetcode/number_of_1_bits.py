class Solution:

    def hammingWeight(self, n):
        count = 0
        while n > 0:
            n = n & (n - 1)
            count = count + 1
        return count


if __name__ == '__main__':
    s = Solution()

    assert 0 == s.hammingWeight(0)
    assert 1 == s.hammingWeight(1)
    assert 1 == s.hammingWeight(2)
    assert 2 == s.hammingWeight(3)
    assert 3 == s.hammingWeight(11)
