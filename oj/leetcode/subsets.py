class Solution:

    def subsets(self, nums):

        def seq_from_integer(integer):
            rv, pos = [], len(nums) - 1
            while integer > 0:
                if integer & 1 == 1:
                    rv.append(nums[pos])
                integer, pos = integer >> 1, pos - 1
            return rv

        if not nums:
            return []
        rv = []
        nums.sort(reverse=True)
        for i in range(0, 2 ** len(nums)):
            rv.append(seq_from_integer(i))

        return rv


if __name__ == '__main__':
    s = Solution()

    print(s.subsets([1, 2]))
