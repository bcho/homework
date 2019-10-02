from typing import List


class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        if len(nums) < 1:
            return 0

        # idea:
        #
        # A[i, j] = A[0, j] - A[0, i-1]
        #
        # we want to find how many A[i, j] = k
        #
        # we can convert the equation to:
        #
        # A[0. i-1] = -k +         A[0. j]
        # ~~~~~~~~~                ~~~~~~~
        # |-> previous calculated   |-> this time calculated (accumulated)
        #
        # so for j, there are F[k - A[0, j]] possible of A[0, i-1],
        # and we don't have to check all i that <= j, because we only care
        # about the times of k - A[0, j]

        total_count = 0
        prefix_sums = {0: 1}
        running_sum = 0
        for idx, num in enumerate(nums):
            # A[0, j]
            running_sum += num
            # A[0, j] - k
            prefix_sum = running_sum - k
            if prefix_sum in prefix_sums:
                # find how many times for A[0, j] - k appeared before
                total_count += prefix_sums[prefix_sum]

            # record A[0, j] for next usage
            if running_sum not in prefix_sums:
                prefix_sums[running_sum] = 0
            prefix_sums[running_sum] += 1

        return total_count
