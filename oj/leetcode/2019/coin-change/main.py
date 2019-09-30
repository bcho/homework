from typing import List


class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        inf = float('inf')
        # set f[a] as the minimum numbers of coins to use to sum up to a
        #
        # so, for each coin:
        #
        #   f[a] = min(
        #       # not use this coin for amount=a
        #       f[a],
        #       # use this coin for amount=a
        #       f[a - coin] + 1
        #   )
        f = [inf] * (amount + 1)
        f[0] = 0
        coins = sorted(coins, reverse=True)
        for coin in coins:
            for a in range(1, amount + 1):
                if a < coin:
                    continue
                f[a] = min(f[a], f[a - coin] + 1)
        if f[amount] == inf:
            return -1
        return f[amount]
