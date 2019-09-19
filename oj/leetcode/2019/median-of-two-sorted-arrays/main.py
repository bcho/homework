from typing import List


class Solution:
    def findMedianSortedArrays(
        self,
        nums1: List[int],
        nums2: List[int]
    ) -> float:
        # median invariant:
        #
        # a[0], a[1], ..., a[m1 - 1] || a[m1], a[m1 + 1], ..., a[len(a) - 1]
        # b[0], b[1], ..., b[m2 - 1] || b[m2], b[m2 + 1], ..., b[len(b) - 1]
        #
        # where (m1 + m2) = half of the size of two arrays:
        #
        #   m1 + m2 = (len(a) + len(b) + 1) // 2 (for both odd and even size)
        #
        #   the median will be:
        #
        #   odd size: max(a[m1 - 1], b[m2 - 1])
        #   even size: max(a[m1 - 1], b[m2 - 1]), min(a[m1], b[m2])
        #
        # sorted invariant
        #
        #  a[m1 - 1] <= a[m1]
        #  b[m2 - 1] <= b[m2]
        #  a[m1 - 1] <= b[m2]
        #  b[m2 - 1] <= a[m1]
        #
        # so we use binary search to find the left most m1 that holds:
        #
        #   b[m2 - 1] <= a[m1]

        def find(a: List[int], b: List[int]):
            # special handle for both odd & even cases
            k = (len(a) + len(b) + 1) // 2
            # binary search in the smaller array
            lidx, ridx = 0, len(a)
            while lidx < ridx:
                maidx = (lidx + ridx) // 2
                mbidx = k - maidx
                if a[maidx] < b[mbidx - 1]:
                    # not hold the invariant, search the right part
                    lidx = maidx + 1
                else:
                    # hold the invariant, shrink the window
                    ridx = maidx

            # special case: median in one array
            aidx, bidx = lidx, k - lidx
            m1 = -(1 << 31)
            if aidx > 0:
                # median exists in the first array
                m1 = max(a[aidx - 1], m1)
            if bidx > 0:
                # median exists in the second array
                m1 = max(b[bidx - 1], m1)
            if (len(a) + len(b)) % 2 == 1:
                return m1

            m2 = 1 << 31
            if aidx < len(a):
                # median exists in the first array
                m2 = min(a[aidx], m2)
            if bidx < len(b):
                # median exists in the second array
                m2 = min(b[bidx], m2)
            return (m1 + m2) / 2

        if len(nums1) < len(nums2):
            return find(nums1, nums2)
        else:
            return find(nums2, nums1)


if __name__ == '__main__':
    s = Solution()
    assert s.findMedianSortedArrays([1, 2, 3], []) == 2
    assert s.findMedianSortedArrays([1, 2], [3]) == 2
    assert s.findMedianSortedArrays([1, 2], [3, 4]) == 2.5
