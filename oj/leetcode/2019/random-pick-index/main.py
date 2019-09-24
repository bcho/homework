import random


class Solution:

    def __init__(self, nums: List[int]):
        self.nums = nums


    def pick(self, target: int) -> int:
        saved_index = -1
        pool_size = 1
        i = 1
        for idx, num in enumerate(self.nums):
            if num != target:
                continue
            if saved_index == -1:
                # special case, take the value
                saved_index = idx
                i = 1
            else:
                if random.random() <= pool_size / (pool_size + i):
                    # replace one item from the pool
                    saved_index = idx
                i = i + 1
        return saved_index
