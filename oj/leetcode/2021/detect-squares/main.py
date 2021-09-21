from collections import defaultdict


class DetectSquares:

    def __init__(self):
        self.X = defaultdict(lambda: defaultdict(lambda: 0))

    def add(self, point: List[int]) -> None:
        x, y = point
        self.X[x][y] += 1        

    def count(self, point: List[int]) -> int:
        rv = 0
        x, y = point
        for y_with_same_x, count_y_with_same_x in self.X[x].items():
            width = abs(y_with_same_x - y)
            if width == 0:
                continue
            for x_with_same_y in (x + width, x - width):
                if x_with_same_y < 0:
                    continue
                if x_with_same_y not in self.X:
                    continue
                if y not in self.X[x_with_same_y]:
                    continue
                count_x_with_same_y = self.X[x_with_same_y][y]
                target_point_count = self.target_point_count_for(x, y, y_with_same_x, x_with_same_y)
                rv += count_y_with_same_x * count_x_with_same_y * target_point_count
                
        return rv
    
    def target_point_count_for(self, x, y, y_with_same_x, x_with_same_y):
        width = abs(x - x_with_same_y)
        # case 1
        if y_with_same_x > y and x_with_same_y > x:
           target_x, target_y = x + width, y + width
        # case 2
        if y_with_same_x > y and x_with_same_y < x:
           target_x, target_y = x - width, y + width
        # case 3
        if y_with_same_x < y and x_with_same_y < x:
           target_x, target_y = x - width, y - width
        # case 4
        if y_with_same_x < y and x_with_same_y > x:
           target_x, target_y = x + width, y - width
        return self.X[target_x][target_y]
        