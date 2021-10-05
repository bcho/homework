class Solution:
    def maxProductPath(self, grid: List[List[int]]) -> int:
        modulo = 10 ** 9 + 7
        memo = {}
        
        def search(coord):
            if coord in memo:
                return memo[coord]
            if coord == (0, 0):
                return (grid[0][0], )
            i, j = coord
            max_value = -2 ** 10
            min_value = 2 ** 10
            if i > 0:
                for value_from_top in search((i - 1, j)):
                    new_value = value_from_top * grid[i][j]
                    max_value = max(max_value, new_value)
                    min_value = min(min_value, new_value)
            if j > 0:
                for value_from_left in search((i, j - 1)):
                    new_value = value_from_left * grid[i][j]
                    max_value = max(max_value, new_value)
                    min_value = min(min_value, new_value)
            memo[coord] = (min_value, max_value)
            return memo[coord]
                
        values = search((len(grid) - 1, len(grid[0]) - 1))
        max_value = max(values)
        
        # print(memo)
        
        if max_value < 0:
            return -1
        return max_value % modulo