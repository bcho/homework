class Solution:

    MAGIC = 2 ** 30

    def minSubArrayLen(self, s, nums):
        left, window_sum, window_size_min = 0, 0, self.MAGIC
        for right, number in enumerate(nums):
            # Move forward.
            window_sum = window_sum + number

            while window_sum >= s:
                current_window_size = right - left + 1
                window_size_min = min(current_window_size, window_size_min)

                # Reduce window.
                window_sum = window_sum - nums[left]
                left = left + 1

        if window_size_min == self.MAGIC:
            window_size_min = 0
        return window_size_min


if __name__ == '__main__':
    s = Solution()
    assert 0 == s.minSubArrayLen(3, [1, 1])
    assert 0 == s.minSubArrayLen(0, [])
    assert 2 == s.minSubArrayLen(7, [2, 3, 1, 2, 4, 3])
    assert 1 == s.minSubArrayLen(1, [1])
    assert 2 == s.minSubArrayLen(3, [1, 2])
    assert 1 == s.minSubArrayLen(2, [1, 2])
    assert 6 == s.minSubArrayLen(15, [2, 3, 1, 2, 4, 3])
