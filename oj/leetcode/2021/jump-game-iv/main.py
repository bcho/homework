class Solution:

    def minJumps(self, arr: List[int]) -> int:
        value_to_indices = {}
        for idx, n in enumerate(arr):
            if n not in value_to_indices:
                value_to_indices[n] = []
            value_to_indices[n].append(idx)

        visited_indices = {0}
        visited_values = set()
        q = [(0, 0)]
        while len(q) > 0:
            nq = []
            for idx, jumps in q:
                if idx == len(arr) - 1:
                    return jumps

                value = arr[idx]
                for idx_with_same_value in value_to_indices[value]:
                    if idx_with_same_value in visited_indices:
                        continue
                    visited_indices.add(idx_with_same_value)
                    nq.append((idx_with_same_value, jumps + 1))
                value_to_indices[value] = []
                if idx + 1 not in visited_indices:
                    visited_indices.add(idx + 1)
                    nq.append((idx + 1, jumps + 1))
                if idx - 1 >= 0 and idx - 1 not in visited_indices:
                    visited_indices.add(idx - 1)
                    nq.append((idx - 1, jumps + 1))
            q = nq

        return -1
