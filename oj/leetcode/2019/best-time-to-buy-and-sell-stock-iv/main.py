from typing import List


class Solution:

    def maxProfit(self, k: int, prices: List[int]) -> int:
        # simple case
        if len(prices) < 2:
            return 0
        if k < 1:
            return 0

        if k > len(prices) // 2:
            # corner case, k is large enough for us to do unlimited
            # transactions, so we just greedily to take the max profit
            max_profit = 0
            for i in range(1, len(prices)):
                if prices[i] > prices[i - 1]:
                    max_profit += prices[i] - prices[i - 1]
            return max_profit

        # Suppose we use d[i][k] to represent the max profit
        # at day i with k times transactions (0 < i < #prices, 0 < k < 3).
        # The recursive formula is:
        #
        #
        #   d[i][k] = max(
        #       # don't do transaction at that day
        #       d[i - 1][k],
        #       # do transaction at that day, then sums with the previous
        #       # maximum profit (j from day 0..i - 1)
        #       prices[i] - (prices[j] - d[j - 1][k - 1])
        #                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~ <- min_cost
        #   )
        d = [0] * (k + 1)
        min_cost = [prices[0]] * (k + 1)
        for i, price in enumerate(prices):
            if i < 1:
                continue

            for K in range(1, k + 1):
                min_cost[K] = min(
                    # already contain the smallest value of min_cost[k]
                    # for j = 0 .. i - 1 (old cases, already the smallest)
                    min_cost[K],
                    # so in this loop, we compare with the new case only:
                    price - d[K - 1],
                )
                d[K] = max(
                    d[K],
                    price - min_cost[K]
                )

        return d[k]


if __name__ == '__main__':
    s = Solution()
    assert s.maxProfit(2, [3, 3, 5, 0, 0, 3, 1, 4]) == 6
    assert s.maxProfit(2, [1, 2, 3, 4, 5]) == 4
    assert s.maxProfit(2, [5, 4, 3, 2, 1]) == 0
    assert s.maxProfit(0, [1, 3]) == 0
    assert s.maxProfit(2, [2, 1, 2, 0, 1]) == 2
