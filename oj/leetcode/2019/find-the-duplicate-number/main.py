from typing import List


class Solution:

    def findDuplication_bit_fields(self, nums: List[int]) -> int:
        import math

        mask_width = 32
        # reduce the outer loop to n/32, but the total loop is still O(n^2)
        for step in range(math.ceil(len(nums) / mask_width)):
            range_start = mask_width * step + 1
            range_end = mask_width * (step + 1)
            visited, mask_scale = 0, mask_width * step
            for num in nums:
                if num < range_start or num > range_end:
                    # not in the check range, skipping
                    continue
                # mark the posision of the number
                mask = 1 << (num - mask_scale - 1)
                if visited & mask > 0:
                    return num
                else:
                    visited = visited | mask

        # should not happen
        assert False

    def findDuplication(self, nums: List[int]) -> int:
        # P1:
        #
        # based on pigeonhole principle, n+1 cells with n items will cause at
        # least one item occur more than once
        #
        # P2:
        #
        # Suppose we're traversing a graph with n items and there is no
        # duplicated item, we can traverse the graph with n jumps. But based on
        # P1, there are at least one duplicated items in the graph, so there is
        # a cycle.
        #
        # To detect the start of the cycle, let's draw a graph:
        #
        #
        #       A -> B -> C -> D \
        #              \         E
        #               \-G <- F /
        #
        # If there are two pointers visiting the graph with different speed,
        # they will meet in a node inside the cycle:
        #
        #   speed(p1) = Q x speed(p2)
        #   handle = the length of the handle
        #   c = the length of the cycle
        #   x = distance that p2 had traversed when two pointers fisrt meet
        #   dis(n) = distance that the pointer had traversed
        #
        # when two pointers meet:
        #
        #   dis(p1) = h + x + cycle (catch up to p2)
        #   dis(p2) = h + x
        #
        # and from the speed, we can know that:
        #
        #   dis(p1) = (Q-1) * dis(p2)
        #
        # combining these:
        #
        #   (Q - 1) * (h + x) = c
        #
        # We can set Q to 2 (which means the p1 is two times fast as p2):
        #
        #   h + x = c, and x = c - h
        #
        # So after p1 had met p2, p2 requires h more steps to finsih one cycle,
        # on the other hand, p2 needs h more steps to return to the start of
        # the cylce. At this time, we can find the start node of the cylce.
        slow, fast = 0, 0
        while True:
            slow = nums[slow]
            fast = nums[nums[fast]]
            if slow == fast:
                # found the cycle
                break

        remaining = 0
        while remaining != slow:
            # advance until reach the start of the cycle
            slow = nums[slow]
            remaining = nums[remaining]
        return slow


if __name__ == '__main__':
    s = Solution()
    assert s.findDuplication([1, 1, 1, 1, 1]) == 1
    assert s.findDuplication([1, 3, 4, 2, 2]) == 2
    assert s.findDuplication([3, 1, 3, 4, 2]) == 3
