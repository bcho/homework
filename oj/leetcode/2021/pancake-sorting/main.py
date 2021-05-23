import random
from typing import List


class Solution:

    def flip(self, arr: List[int], k: int) -> List[int]:
        assert 0 <= k <= len(arr)

        flipped = arr[:k][::-1] + arr[k:]
        # print(f'flip at={k}, flipped={flipped}')
        return flipped

    def pancakeSort(self, arr: List[int]) -> List[int]:
        seq = []
        for n in range(len(arr), 1, -1):
            # find the largest element in the sub array
            largest, largest_idx = arr[0], 0
            for idx in range(1, n):
                v = arr[idx]
                if v > largest:
                    largest, largest_idx = v, idx

            # print(f'largest={largest}, largest_idx={largest_idx} arr={arr}')

            if largest_idx == n - 1:
                # no need to flip
                continue
            if largest_idx != 0:
                # flip to beginning
                seq.append(largest_idx + 1)
                arr = self.flip(arr, largest_idx + 1)
            # flip to end
            seq.append(n)
            arr = self.flip(arr, n)

        return seq

    def pancakeSort_bfs(self, arr: List[int]) -> List[int]:

        arr_sorted = sorted(arr)

        def is_sorted(a: List[int]) -> bool:
            for idx, val in enumerate(a):
                if arr_sorted[idx] != val:
                    return False

            return True

        if is_sorted(arr):
            return []

        def encode_arr_state(a: List[int]) -> str:
            return '|'.join([str(i) for i in a])

        known_states = set()
        candidates = [(arr, encode_arr_state(arr), [])]
        while len(candidates) > 0:
            candidate, candidate_state, candidate_path = candidates[0]
            candidates = candidates[1:]
            known_states.add(candidate_state)
            for k in range(2, len(arr) + 1):
                flipped_candidate_path = candidate_path + [k]
                flipped_candidate = self.flip(candidate, k)
                # print(candidate, flipped_candidate, flipped_candidate_path)
                if is_sorted(flipped_candidate):
                    return flipped_candidate_path
                flipped_candidate_state = encode_arr_state(flipped_candidate)
                if flipped_candidate_state in known_states:
                    # seen before
                    continue
                n = (flipped_candidate, flipped_candidate_state, flipped_candidate_path)
                candidates.append(n)

        return []


if __name__ == '__main__':
    s = Solution()

    def replay(a: List[int], seq: List[int]):
        sorted_a = sorted(a)

        for k in seq:
            a = s.flip(a, k)
        assert sorted_a == a, a


    cases = [
        [1, 2, 3],
        [3, 2, 4, 1],
        [3, 2, 1],
        [3, 2, 1, 4],
        [10,5,1,6,3,8,2,4,7,9],
    ]
    for i in range(10):
        seq = [i for i in range(100)]
        random.shuffle(seq)
        cases.append(seq)


    for c in cases:
        print(f'{c}')
        seq = s.pancakeSort(c)
        print(f'seq={seq}')
        replay(c, seq)
