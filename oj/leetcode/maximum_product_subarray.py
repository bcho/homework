class Solution:

    def maxProduct(self, nums):
        if not nums:
            return 0

        fmax, fmin = [0] * len(nums), [0] * len(nums)
        fmax[0], fmin[0] = nums[0], nums[0]

        m = nums[0]
        for i, num in enumerate(nums[1:]):
            candidates = (
                fmax[i] * num,
                fmin[i] * num,
                num
            )
            fmax[i + 1], fmin[i + 1] = max(candidates), min(candidates)
            m = max(fmax[i + 1], m)

        return m

if __name__ == '__main__':
    s = Solution()

    assert -2 == s.maxProduct([-2])
    assert 6 == s.maxProduct([2, 3, -2, 4])
    assert 48 == s.maxProduct([2, 3, -2, 4, -1])
    assert 1 == s.maxProduct([-1, 1, -1])
    assert 0 == s.maxProduct([-1, 0])
