class Point(object):

    def __init__(self, x, y):
        self.x, self.y = x, y

    @staticmethod
    def from_tuple(xy):
        return Point(*xy)

    @staticmethod
    def create_batch(list_of_xy):
        return [Point.from_tuple(i) for i in list_of_xy]

    def __str__(self):
        return '({r.x}, {r.y})'.format(r=self)

    def __repr__(self):
        return self.__str__()


INF = 2 << 30


class Solution(object):

    # O(n^2)
    def maxPoints(self, points):

        def calculate_slope(a, b):
            dx, dy = a.x - b.x, a.y - b.y
            if dx == 0:
                return INF
            return dy / float(dx)

        def is_same_point(a, b):
            return a.x == b.x and a.y == b.y

        max_count = 0

        for start_point in points:
            slopes_to_this_point = {}
            duplicate_points = 0

            for other_point in points:
                if start_point is other_point:
                    continue

                if is_same_point(start_point, other_point):
                    duplicate_points += 1
                    continue

                slope = calculate_slope(start_point, other_point)
                if slope not in slopes_to_this_point:
                    slopes_to_this_point[slope] = 0
                slopes_to_this_point[slope] += 1

            slopes_count = sorted(slopes_to_this_point.values(), reverse=True)
            max_slopes_count = slopes_count[0] if slopes_count else 0

            max_count = max(max_count, max_slopes_count + duplicate_points + 1)

        return max_count


if __name__ == '__main__':
    points = Point.create_batch([])
    print(Solution().maxPoints(points))
