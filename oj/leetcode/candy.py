class Solution:
    # O(nlogn)
    def candy(self, ratings):
        N = len(ratings)

        def adjust_candies(pos, ratings, candies):

            def check_neighbour(pos, neighbour_pos, ratings, candies):
                if (ratings[pos] > ratings[neighbour_pos] and
                        candies[pos] <= candies[neighbour_pos]):
                    return candies[neighbour_pos] - candies[pos] + 1
                return 0

            left_adjust, right_adjust = 0, 0
            if pos > 0:
                left_adjust = check_neighbour(pos, pos - 1, ratings, candies)
            if pos < len(ratings) - 1:
                right_adjust = check_neighbour(pos, pos + 1, ratings, candies)

            return max(left_adjust, right_adjust)

        sorted_ratings = sorted(list(enumerate(ratings)), key=lambda x: x[1])
        candies = [1] * N

        for pos, rating in sorted_ratings[1:]:
            candies[pos] += adjust_candies(pos, ratings, candies)

        return sum(candies)
