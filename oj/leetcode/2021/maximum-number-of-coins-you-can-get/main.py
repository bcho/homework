from typing import List


class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        piles = sorted(piles, reverse=True)
        pick_times = len(piles) // 3
        picked_by_me = 0
        for i in range(pick_times):
            picked_by_me += piles[i * 2 + 1]

        return picked_by_me
