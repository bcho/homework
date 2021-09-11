class Solution:
    def diagonalSort(self, mat: List[List[int]]) -> List[List[int]]:
        max_row, max_col = len(mat) - 1, len(mat[0]) - 1
        row, col = 0, max_col - 1
        while True:
            a = []
            print(f'starting from {row},{col}')
            arow, acol = row, col
            while acol >= 0 and arow <= max_row and acol <= max_col:
                # print(arow, acol)
                a.append(mat[arow][acol])
                arow += 1
                acol += 1
            a = sorted(a)
            arow, acol, i = row, col, 0
            while acol >= 0 and arow <= max_row and acol <= max_col:
                mat[arow][acol] = a[i]
                arow += 1
                acol += 1
                i += 1
            print(mat, a)
            col = col - 1
            if col < 0:
                # print(mat[row])
                row = row + 1
                col = 0
            if row > max_row:
                break
        return mat
