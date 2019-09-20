from typing import List


class Solution:

    class Heap:

        def __init__(self, cmp):
            self.cmp = cmp
            self.items = []
            self.key_to_item_idx = {}
            self.item_idx_to_key = {}

        @property
        def size(self) -> int:
            return len(self.items)

        def add(self, item: int, item_key: int):
            self.items.append(item)
            item_idx = len(self.items) - 1
            self.key_to_item_idx[item_key] = item_idx
            self.item_idx_to_key[item_idx] = item_key

            self._swim(item_idx)

        def pop(self) -> int:
            assert len(self.items) > 0
            return self._remove_item(0)

        def remove_by_key(self, item_key: int):
            if item_key not in self.key_to_item_idx:
                return
            return self._remove_item(self.key_to_item_idx[item_key])

        @property
        def peak(self) -> int:
            assert len(self.items) > 0
            return self.items[0]

        def _parent_idx(self, idx):
            return (idx - 1) // 2

        def _left_child_idx(self, idx):
            return idx * 2 + 1

        def _right_child_idx(self, idx):
            return idx * 2 + 2

        def _remove_item(self, item_idx) -> int:
            assert 0 <= item_idx < len(self.items)
            item_key = self.item_idx_to_key[item_idx]
            self._swap(item_idx, len(self.items) - 1)
            self.item_idx_to_key.pop(len(self.items) - 1)
            self.key_to_item_idx.pop(item_key)
            rv = self.items.pop()

            self._sink(item_idx)

            return rv, item_key

        def _swap(self, a, b):
            akey, bkey = self.item_idx_to_key[a], self.item_idx_to_key[b]
            self.items[a], self.items[b] = self.items[b], self.items[a]
            self.key_to_item_idx[akey] = b
            self.key_to_item_idx[bkey] = a
            self.item_idx_to_key[a] = bkey
            self.item_idx_to_key[b] = akey

        def _sink(self, parent_idx):
            while True:
                left_child_idx = self._left_child_idx(parent_idx)
                if left_child_idx >= len(self.items):
                    # reached leave
                    break
                child_idx = left_child_idx
                child_value = self.items[left_child_idx]
                right_child_idx = self._right_child_idx(parent_idx)
                if right_child_idx < len(self.items):
                    if self.cmp(
                        self.items[right_child_idx],
                        child_value,
                    ):
                        child_idx = right_child_idx
                        child_value = self.items[right_child_idx]
                if self.cmp(self.items[parent_idx], child_value):
                    # adjust finished
                    break
                self._swap(parent_idx, child_idx)
                parent_idx = child_idx

        def _swim(self, child_idx):
            while child_idx > 0:
                parent_idx = self._parent_idx(child_idx)
                if self.cmp(self.items[parent_idx], self.items[child_idx]):
                    # already match
                    break
                self._swap(parent_idx, child_idx)
                child_idx = parent_idx

    def medianSlidingWindow_(self, nums: List[int], k: int) -> List[float]:
        if k < 1:
            return []
        if len(nums) < 1:
            return []

        rv = []
        left_part = Solution.Heap(lambda a, b: a > b)
        right_part = Solution.Heap(lambda a, b: a < b)

        def rebalance():
            while right_part.size > left_part.size + 1:
                left_part.add(*right_part.pop())
            while left_part.size > right_part.size:
                right_part.add(*left_part.pop())

        def add_item(item, item_idx):
            if right_part.size == 0 or item > right_part.peak:
                right_part.add(item, item_idx)
            else:
                left_part.add(item, item_idx)

        def get_median():
            if left_part.size == right_part.size:
                return (left_part.peak + right_part.peak) / 2
            return right_part.peak

        idx = 0
        while idx < k:
            add_item(nums[idx], idx)
            rebalance()
            idx = idx + 1
        rv.append(get_median())

        while idx < len(nums):
            window_left_idx = idx - k
            left_part.remove_by_key(window_left_idx)
            right_part.remove_by_key(window_left_idx)
            add_item(nums[idx], idx)
            idx = idx + 1
            rebalance()
            rv.append(get_median())

        return rv

    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        if k < 1:
            return []
        if len(nums) < 1:
            return []

        # we maintain a window that is sorted,
        # for the items with same value, they are sorted by idx
        # (i.e. first value in the left)
        #
        # this step is: O(klogk)
        window = sorted(nums[:k])

        def bsearch_leftmost(num):
            if len(window) < 1:
                return 0
            lidx, ridx = 0, len(window)
            while lidx < ridx:
                m = (lidx + ridx) // 2
                if window[m] < num:
                    lidx = m + 1
                else:
                    ridx = m
            return lidx

        def bsearch_rightmost(num):
            if len(window) < 1:
                return 0
            lidx, ridx = 0, len(window)
            while lidx < ridx:
                m = (lidx + ridx) // 2
                if window[m] > num:
                    ridx = m
                else:
                    lidx = m + 1
            return lidx

        def get_median():
            if k % 2 == 0:
                return (window[k // 2] + window[k // 2 - 1]) / 2
            return window[k // 2]

        rv = [get_median()]
        for idx, num in enumerate(nums[k:], k):
            # Each step, we shift the window to right, so we use
            # bsearch_leftmost to find the position of the nums[idx-k]
            # and remove it from the window.
            #
            # The bsearch step is O(logk)
            to_remove = bsearch_leftmost(nums[idx - k])
            # This takes O(k)
            window.pop(to_remove)
            # Next, we find a proper posistion (the right most index)
            # for the new value and insert it to the window
            to_insert = bsearch_rightmost(num)
            # This takes O(k)
            window.insert(to_insert, num)

            # calculate the median for this step
            rv.append(get_median())

        return rv


if __name__ == '__main__':
    s = Solution()
    assert s.medianSlidingWindow([1, 3, -1], 1) == [1, 3, -1]
    assert s.medianSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3) == [
        1, -1, -1, 3, 5, 6,
    ]
    assert s.medianSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3) == [
        1, -1, -1, 3, 5, 6,
    ]

    assert s.medianSlidingWindow(
        [1, 3, 3, 5],
        2,
    ) == [2, 3, 4]

    assert s.medianSlidingWindow(
        [1, 3, 3, 5],
        3,
    ) == [3, 3]

    assert s.medianSlidingWindow(
        [5, 3, 3, 1],
        3,
    ) == [3, 3]

    assert s.medianSlidingWindow([1] * 100, 2) == [1] * 99
