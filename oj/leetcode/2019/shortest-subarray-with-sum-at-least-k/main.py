from typing import List


class Solution:

    # TLE
    def shortestSubarray_tle(self, A: List[int], K: int) -> int:
        if len(A) < 1:
            return -1
        last_f = []
        f = []
        s = [] * (len(A) + 1)
        s[0] = A[0]
        for idx, a in enumerate(A):
            if a >= K:
                return 1
            last_f.append(a)
            f.append(a)
            s[idx + 1] = s[idx] + a
        for n in range(2, len(A) + 1):
            for idx, a in enumerate(A[n:], n):
                f[idx] = last_f[idx - 1] + a
                if f[idx] >= K:
                    return n + 1
            last_f = f[:]
        return -1

    def shortestSubarray(self, A: List[int], K: int) -> int:
        from collections import deque

        if len(A) < 1:
            return -1
        ss = [0]
        for a in A:
            # calculate the rolling sum
            # s[1] = a[0]
            # s[2] = a[0] + a[1]
            # ...
            ss.append(ss[-1] + a)

        rv = float('inf')
        # invariants:
        #
        # 1. increase order of ss (if the sum decrease, it cannot reach K)
        # 2. last value - first value < K
        #    (the distance of the later items will bigger than the previous)
        q = deque()
        for idx, s in enumerate(ss):
            while len(q) > 0:
                # invariant 1
                if ss[q[-1]] <= s:
                    break
                q.pop()
            while len(q) > 0:
                # invariant 2
                if s - ss[q[0]] < K:
                    break
                # calculate the distance
                rv = min(rv, idx - q[0])
                q.popleft()
            q.append(idx)
        if rv <= len(A):
            return rv
        return -1


if __name__ == '__main__':
    s = Solution()
    assert s.shortestSubarray([-28, 81, -20, 28, -29], 89) == 3
    assert s.shortestSubarray([48, 99, 37, 4, -31], 140) == 2
    assert s.shortestSubarray([1], 1) == 1
    assert s.shortestSubarray([1, 2], 4) == -1
    assert s.shortestSubarray([2, -1, 2], 3) == 3
    assert s.shortestSubarray([2, -1, 2, 4], 5) == 2
