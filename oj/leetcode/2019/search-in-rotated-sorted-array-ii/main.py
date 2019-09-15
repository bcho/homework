from typing import List


class Solutioin:

    def search(self, nums: List[int], target: int) -> bool:
        # simple cases
        if len(nums) < 1:
            return False

        def binary_search_range(l: int, r: int) -> bool:
            if l > r:
                return False
            m = (l + r) // 2
            if nums[m] == target:
                return True
            if nums[l] >= nums[r]:
                # no a *normal* case, need to visit the both sub-trees
                return (
                    binary_search_range(l, m - 1)
                    or binary_search_range(m + 1, r)
                )
            if nums[m] > target:
                # binary search the left sub tree
                return binary_search_range(l, m - 1)
            if nums[m] < target:
                # binary search the right sub tree
                return binary_search_range(m + 1, r)

        return binary_search_range(0, len(nums) - 1)


if __name__ == '__main__':
    s = Solutioin()
    assert s.search([1, 2, 3, 4, 5], 3)
    assert not s.search([1, 2, 3, 4, 5], 8)
    assert s.search([2, 5, 6, 0, 0, 1, 2], 0)
    assert not s.search([2, 5, 6, 0, 0, 1, 2], 3)
    assert s.search([2, 5, 6, 0, 0, 1, 2], 2)
