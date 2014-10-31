class Solution:

    def generate(self, numRows):
        num_rows = numRows
        triangles = [[1], [1, 1]]

        if num_rows <= 2:
            return triangles[:num_rows]

        for i in range(2, num_rows):
            seq = [1]
            last_row = triangles[i - 1]
            for j, _ in enumerate(last_row):
                if j >= len(last_row) - 1:
                    break
                seq.append(last_row[j] + last_row[j + 1])
            seq.append(1)

            triangles.append(seq)

        return triangles


if __name__ == '__main__':
    s = Solution()

    print(s.generate(0))
    print(s.generate(1))
    print(s.generate(2))
    print(s.generate(3))
    print(s.generate(5))
