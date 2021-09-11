class Solution:
    def smallestDivisor(self, nums: List[int], threshold: int) -> int:
        def sum_by_divisor(d: int) -> int:
            s = 0
            for n in nums:
                s += n//d
                if n % d > 0:
                    s += 1
            return s

        l, r = 1, max(nums)
        while True:
            mid = (l + r) // 2
            if mid < l or mid >= r:
                return mid
            sum_for_current_divisor = sum_by_divisor(mid)
            if sum_for_current_divisor > threshold:
                # we need to search the area that > current divisor
                l = mid + 1
            else:
                # we try to search the area that <= current divisor
                r = mid
