class Solution:

    def majorityElement(self, nums):
        counter, majority_count, majority_element = {}, -1, None
        for num in nums:
            if num not in counter:
                counter[num] = 1
            else:
                counter[num] = counter[num] + 1
            if counter[num] > majority_count:
                majority_count = counter[num]
                majority_element = num

        if majority_count > len(nums) / 2:
            return majority_element


if __name__ == '__main__':
    s = Solution()

    assert 1 == s.majorityElement([1, 1])
