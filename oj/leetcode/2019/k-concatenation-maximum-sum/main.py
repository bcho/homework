from typing import List


class Solution:
    def kConcatenationMaxSum(self, arr: List[int], k: int) -> int:
        if len(arr) < 1:
            return 0
        if k < 1:
            return 0

        mod = 10**9 + 7

        def modulo(x):
            if x > 0:
                return x % mod
            return x

        # max sub sum in one array
        # maximum sub sum
        max_sub_sum, last = 0, 0
        for a in arr:
            last = modulo(max(a + last, a))
            max_sub_sum = max(last, max_sub_sum)
        if k == 1:
            return max_sub_sum

        sum_arr = sum(arr)

        prefix_sum, suffix_sum = 0, 0
        running_prefix_sum, running_suffix_sum = 0, 0
        for i in range(len(arr)):
            a = arr[len(arr) - i - 1]
            running_prefix_sum = modulo(a + running_prefix_sum)
            if running_prefix_sum > prefix_sum:
                prefix_sum = running_prefix_sum

            a = arr[i]
            running_suffix_sum = modulo(a + running_suffix_sum)
            if running_suffix_sum > suffix_sum:
                suffix_sum = running_suffix_sum

        # cases
        #
        #    1. prefix-sum | arr | arr | ... | arr | arr | suffix-sum
        #    2. prefix-sum | suffix-sum
        #    3. max-sub-sum
        #
        # when sum(arr) < 0: only 2 / 3
        if sum_arr < 0:
            return max(
                max_sub_sum,
                prefix_sum + suffix_sum
            )
        # when sum(arr) >= 0: only 1 / 3
        else:
            return max(
                max_sub_sum,
                modulo(sum_arr * (k - 2)) + prefix_sum + suffix_sum
            )
