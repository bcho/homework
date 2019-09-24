class Solution:

    def findKthNumber(self, m: int, n: int, k: int) -> int:
        assert m > 0
        assert n > 0
        assert 1 <= k <= m * n + 1

        # matrix:
        #
        # m ->
        # 1 2 3 4 5    n
        # 2 4 (*)6 8 10   |
        # 3 6 9 12 15
        # ...
        #
        # we count from top-left, with down-to-right order:
        #
        # for 6, which is the 8th smallest number in the matrix
        # every numbers before it are smaller or equal than it,
        # and every numbers after it are bigger or equal than it.
        #
        # so this is a monotonic ordered sequence, we can use binary search
        # to find the k

        def count(idx):
            c = 0
            for mi in range(1, m + 1):
                can_take = idx // mi
                if can_take > n:
                    # max count for this column
                    can_take = n
                c += can_take
            return c

        lidx, ridx = 1, m * n + 1
        while lidx < ridx:
            midx = (lidx + ridx) // 2
            if count(midx) >= k:
                # found enough count at this index, shrink the window to left
                ridx = midx
            else:
                # no enough count at this index, shrink the window to right
                lidx = midx + 1
        return lidx


if __name__ == '__main__':
    s = Solution()
    assert s.findKthNumber(3, 3, 5) == 3
    assert s.findKthNumber(2, 3, 6) == 6
