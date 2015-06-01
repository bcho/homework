class Solution:

    def findKthLargest(self, nums, k):

        def select(l, r):
            median = (l + r) / 2

            nums[l], nums[median] = nums[median], nums[l]

            i, j = l + 1, r
            while i <= j:
                if nums[i] <= nums[l]:
                    nums[j], nums[i] = nums[i], nums[j]
                    j = j - 1
                else:
                    i = i + 1
            nums[l], nums[j] = nums[j], nums[l]

            if j > k - 1:
                return select(l, j - 1)
            if j < k - 1:
                return select(j + 1, r)
            return nums[j]

        return select(0, len(nums) - 1)


if __name__ == '__main__':
    s = Solution()

    assert 5 == s.findKthLargest([3, 2, 1, 5, 6, 4], 2)
    assert 6 == s.findKthLargest([3, 2, 1, 5, 6, 4], 1)
    assert 1 == s.findKthLargest([3, 2, 1, 5, 6, 4], 6)
    assert 4 == s.findKthLargest([3, 2, 1, 5, 6, 4], 3)
