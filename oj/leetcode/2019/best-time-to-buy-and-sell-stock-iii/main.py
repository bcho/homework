from typing import List


class Solution:

    def maxProfit(self, prices: List[int]) -> int:
        # simple case
        if len(prices) < 2:
            return 0

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
        d = [[0, 0, 0] for _ in prices]
        min_cost = [prices[0], prices[0], prices[0]]
        for i, price in enumerate(prices):
            if i < 1:
                continue

            for k in (1, 2):
                min_cost[k] = min(
                    # already contain the smallest value of min_cost[k]
                    # for j = 0 .. i - 1 (old cases, already the smallest)
                    min_cost[k],
                    # so in this loop, we compare with the new case only:
                    prices[i] - d[i - 1][k - 1],
                )
                d[i][k] = max(
                    d[i - 1][k],
                    prices[i] - min_cost[k]
                )

        return d[len(prices) - 1][2]


if __name__ == '__main__':
    s = Solution()
    assert s.maxProfit([3, 3, 5, 0, 0, 3, 1, 4]) == 6
    assert s.maxProfit([1, 2, 3, 4, 5]) == 4
    assert s.maxProfit([5, 4, 3, 2, 1]) == 0
