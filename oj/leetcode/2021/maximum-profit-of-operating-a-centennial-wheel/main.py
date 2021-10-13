class Solution:
    def minOperationsMaxProfit(self, customers: List[int], boardingCost: int, runningCost: int) -> int:
        waiting_customers_count = 0
        maximum_profit, maximum_profit_round = -1, -1
        profit_so_far = 0
        round_idx = 1
        while True:
            if round_idx <= len(customers):
                customers_count = customers[round_idx - 1]
                waiting_customers_count += customers_count
            onboarded_customers_count = min(waiting_customers_count, 4)
            waiting_customers_count -= onboarded_customers_count
            profit_this_round = onboarded_customers_count * boardingCost - runningCost
            profit_so_far += profit_this_round
            # print(f'{onboarded_customers_count} {waiting_customers_count} {profit_this_round} {profit_so_far} {maximum_profit}')
            if profit_so_far > maximum_profit:
                maximum_profit = profit_so_far
                maximum_profit_round = round_idx
            
            
            round_idx += 1
            if waiting_customers_count == 0 and round_idx > len(customers):
                break
                
        if maximum_profit < 1:
            return -1
        return maximum_profit_round