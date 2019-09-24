from typing import List
import random


class Solution:

    def __init__(self, w: List[int]):
        # preprocess the weight
        # [1, 2, 3] -> [1, 3, 6]
        #
        # means:
        #
        # 0<------->1<------->3<--------->6
        #   idx = 0    idx = 1   idx = 2
        self.w = w
        for i in range(1, len(w)):
            self.w[i] += self.w[i-1]

    def pickIndex(self) -> int:
        # generate a number in the range
        w = random.randint(0, self.w[-1] - 1) + 1
        # find the right most index for the number
        lidx, ridx = 0, len(self.w) - 1
        while lidx < ridx:
            midx = (lidx + ridx) // 2
            if self.w[midx] >= w:
                ridx = midx
            else:
                lidx = midx + 1
        return lidx
