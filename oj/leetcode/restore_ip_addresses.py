class Solution:

    def restoreIpAddresses(self, s):
        s_len = len(s)
        if s_len < 3 or s_len > 12:
            return []

        restored = []

        def previous_dot_pos(dots, placed_dots):
            if placed_dots == 0:
                return 0
            return dots[placed_dots - 1]

        def make_part_from_range(i, j):
            return s[i:j]

        def restore_from_dots(dots):
            m = lambda x, y: str(make_part_from_range(x, y))
            return '.'.join([m(0, dots[0]), m(dots[0], dots[1]),
                             m(dots[1], dots[2]), m(dots[2], s_len)])

        def is_part_validate(part):
            return (part and
                    (not (part.startswith('0') and len(part) > 1)) and
                    0 <= int(part) < 256)

        def restore(dots, placed_dots):
            if placed_dots == 3:
                last_part = make_part_from_range(dots[2], s_len)
                if is_part_validate(last_part):
                    restored.append(restore_from_dots(dots))
                return

            previous = previous_dot_pos(dots, placed_dots)
            for i in range(previous + 1, s_len):
                if s_len - i > (3 - placed_dots) * 3:
                    continue
                part = make_part_from_range(previous, i)
                if not is_part_validate(part):
                    continue
                restore(dots + [i], placed_dots + 1)

        restore([], 0)

        return restored


if __name__ == '__main__':
    s = Solution()
    print(s.restoreIpAddresses('10010'))
