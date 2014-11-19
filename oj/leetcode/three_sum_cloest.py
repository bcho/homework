class Solution:

    def threeSumCloest(self, num, target):
        num.sort()
        num_len = len(num)

        def three_sum(num, remains):
            i = 0
            while i < num_len:
                wanted = remains - num[i]
                j, k = i + 1, num_len - 1
                while j < k:
                    two_sum = num[j] + num[k]
                    if two_sum == wanted:
                        return True
                        j, k = j + 1, k - 1

                        # Skip duplicate entries.
                        while j < k and num[j - 1] == num[j]:
                            j = j + 1
                        while j < k and num[k + 1] == num[k]:
                            k = k - 1
                    elif two_sum < wanted:
                        j = j + 1
                    elif two_sum > wanted:
                        k = k - 1
                i = i + 1

                # Skip duplicate entries.
                while i < num_len and num[i - 1] == num[i]:
                    i = i + 1
            return False

        gap = 0
        while True:
            if three_sum(num, target - gap):
                return target - gap
            if gap != - gap and three_sum(num, target + gap):
                return target + gap
            gap = gap + 1


if __name__ == '__main__':
    s = Solution()
    print(s.threeSumCloest([-1, 2, 1, -4], 1))
