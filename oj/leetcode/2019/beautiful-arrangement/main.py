class Solution:
    def countArrangement(self, N: int) -> int:
        times = 0

        def place(idx, to_use):
            nonlocal times

            if len(to_use) < 1:
                times += 1
                return
            for num in to_use:
                if num % idx == 0 or idx % num == 0:
                    # ok to proceed
                    place(idx - 1, to_use - set([num]))

        # NOTE: start from back is faster (smaller search space)
        place(N, {i+1 for i in range(N)})
        return times
