class Solution:

    def isValidSudoku(self, board):

        def _is_valid_row(r):
            s = {}
            for i in filter(lambda x: x != '.', r):
                if i in s:
                    return False
                if i not in "123456789":
                    return False
                s[i] = True

            return True

        def is_valid_row(r):
            rv = _is_valid_row(r)

            if not rv:
                print(r)

            return rv

        for i in range(9):
            row = [board[i][j] for j in range(9)]
            if not is_valid_row(row):
                return False

            col = [board[j][i] for j in range(9)]
            if not is_valid_row(col):
                return False

        bounds = [((0, 0), (2, 2)), ((0, 3), (2, 5)), ((0, 6), (2, 8)),
                  ((3, 0), (5, 2)), ((3, 3), (5, 5)), ((3, 6), (5, 8)),
                  ((6, 0), (8, 2)), ((6, 3), (8, 5)), ((6, 6), (8, 8))]

        for (sx, sy), (ex, ey) in bounds:
            square = []
            while sx <= ex:
                i = sy
                while i <= ey:
                    square.append(board[sx][i])
                    i = i + 1
                sx = sx + 1
            if not is_valid_row(square):
                return False

        return True


if __name__ == '__main__':
    s = Solution()

    print(s.isValidSudoku([
        "....5..1.",
        ".4.3.....",
        ".....3..1",
        "8......2.",
        "..2.7....",
        ".15......",
        ".....2...",
        ".2.9.....",
        "..4......"
    ]))
