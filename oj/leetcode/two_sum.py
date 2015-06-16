class Solution:

    def twoSum(self, nums, target):
        hashed_nums = {}
        for i, num in enumerate(nums):
            num_pos = i + 1

            other_num = target - num
            other_num_pos = hashed_nums.get(other_num)
            if other_num_pos:
                return other_num_pos, num_pos

            if num_pos not in hashed_nums:
                hashed_nums[num] = num_pos


if __name__ == '__main__':
    s = Solution()

    rv = s.twoSum([2, 7, 11, 15], 9)
    assert 1 == rv[0]
    assert 2 == rv[1]

    rv = s.twoSum([2, 2, 7, 11, 15], 4)
    assert 1 == rv[0]
    assert 2 == rv[1]
