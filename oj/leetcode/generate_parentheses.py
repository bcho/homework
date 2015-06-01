class Solution:

    def generateParenthesis(self, n):
        generated = []

        def place_left(seq, placed_left, placed_right):
            if placed_right == n:
                generated.append(''.join(seq))
                return

            for count_left in range(1, n - placed_left + 1):
                seq = seq + ['('] * count_left
                place_right(seq, placed_left + count_left, placed_right)
                seq = seq[:-count_left]

        def place_right(seq, placed_left, placed_right):
            for count_right in range(1, placed_left - placed_right + 1):
                seq = seq + [')'] * count_right
                place_left(seq, placed_left, placed_right + count_right)
                seq = seq[:-count_right]

        place_left([], 0, 0)

        return generated


if __name__ == '__main__':
    s = Solution()
    print(s.generateParenthesis(4))
