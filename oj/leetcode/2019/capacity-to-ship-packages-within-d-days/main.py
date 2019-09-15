from typing import List


class Solution:

    def shipWithinDays(self, weights: List[int], D: int) -> int:
        # the simulation takes O(len(weights)) = O(n)
        def can_ship_with_capacity(capacity: int) -> bool:
            days_used, weight_loaded = 1, 0
            for weight_to_load in weights:
                if weight_loaded + weight_to_load <= capacity:
                    # can load in this day
                    weight_loaded += weight_to_load
                else:
                    # start a new day
                    days_used += 1
                    if days_used > D:
                        # unable to finish the task
                        return False
                    weight_loaded = weight_to_load
            return days_used <= D

        # impossible case
        if D < 1:
            return -1

        weights_sum = sum(weights)

        # the smallest possible capacity
        min_capacity = max(weights)

        # max capacity: finish in 1 day
        max_capacity = weights_sum

        # the binary search takes O(log(weights_sum)) ~ Olog(10e7) ~ 23
        while min_capacity < max_capacity:
            try_capacity = (min_capacity + max_capacity) // 2
            if can_ship_with_capacity(try_capacity):
                # can ship with this capacity -> try smaller
                max_capacity = try_capacity
            else:
                # cannot ship with this capacity -> try bigger
                min_capacity = try_capacity + 1
        return max_capacity


if __name__ == '__main__':
    s = Solution()
    assert s.shipWithinDays([1, 2, 3, 4, 5, 6, 7, 8, 9, 10], 5) == 15
    assert s.shipWithinDays([1], 5) == 1
    assert s.shipWithinDays([3, 2, 2, 4, 1, 4], 3) == 6
    assert s.shipWithinDays([1, 2, 3, 1, 1], 4) == 3
    assert s.shipWithinDays([10, 10, 100], 1) == 120
    assert s.shipWithinDays([1, 1, 100], 2) == 100
