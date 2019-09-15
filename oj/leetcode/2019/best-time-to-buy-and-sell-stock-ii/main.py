from typing import List


class Solution:

    def maxProfit(self, prices: List[int]) -> int:
        # simple cases
        if len(prices) < 2:
            return 0

        max_profit = 0

        # marks the day with lowest/highest stock price in range
        lowest_price, highest_price = prices[0], prices[0]
        for i in range(1, len(prices)):
            if prices[i] >= highest_price:
                # keep searching for the peak price
                highest_price = prices[i]
            else:
                # peak price found, sell the stock in hand
                max_profit += highest_price - lowest_price
                # start a new range
                lowest_price, highest_price = prices[i], prices[i]
        # last hand
        max_profit += highest_price - lowest_price

        return max_profit


if __name__ == '__main__':
    s = Solution()
    assert s.maxProfit([1, 2, 3]) == 2
    assert s.maxProfit([7, 1, 5, 3, 6, 4]) == 7
    assert s.maxProfit([1, 2, 3, 4, 5]) == 4
    assert s.maxProfit([1, 1, 1, 1, 2]) == 1
