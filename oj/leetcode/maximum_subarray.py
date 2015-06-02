class Solution:

    def maxSubArray(self, nums):
        if not nums:
            return 0

        f = [0] * len(nums)
        f[0] = nums[0]

        m = nums[0]
        for i, num in enumerate(nums[1:]):
            f[i + 1] = max(f[i] + num, num)
            m = max(m, f[i + 1])

        return m


if __name__ == '__main__':
    s = Solution()

    assert -1 == s.maxSubArray([-1])
    assert 6 == s.maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4])
    assert 1 == s.maxSubArray([1, -1, 1])
    assert -1 == s.maxSubArray([-3, -1, -2])
