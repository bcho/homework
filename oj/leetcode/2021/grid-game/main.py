class Solution:
    
    def gridGame(self, grid: List[List[int]]) -> int:
        sum_first_row = sum(grid[0])
        
        maximum_score_for_second_robot = [None] * len(grid[0])
        sum_for_first_row_so_far = 0
        sum_for_second_row_so_far = 0
        for y in range(0, len(grid[0])):
            sum_for_first_row_so_far += grid[0][y]
            score_for_second_robot_using_first_row = sum_first_row - sum_for_first_row_so_far
            score_for_second_robot_using_second_row = sum_for_second_row_so_far
            sum_for_second_row_so_far += grid[1][y]
            maximum_score_for_second_robot[y] = max(score_for_second_robot_using_first_row, score_for_second_robot_using_second_row)
            
        print(maximum_score_for_second_robot)
            
        return min(maximum_score_for_second_robot)