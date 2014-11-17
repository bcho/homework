class Solution:

    # ~ O(n^3)
    def threeSum_tle(self, num):
        pairs = {}
        for i, a in enumerate(num):
            for j, b in enumerate(num):
                if i == j:
                    continue
                wanted = - (a + b)
                if wanted not in pairs:
                    pairs[wanted] = []
                pairs[wanted].append(((i, j), (a, b)))

        solutions = set()
        for i, c in enumerate(num):
            if c not in pairs:
                continue
            for calculated in pairs[c]:
                used_idx, (a, b) = calculated
                if i not in used_idx:
                    solutions.add(tuple(sorted([a, b, c])))

        return list(solutions)

    # O(n^2)
    def threeSum(self, num):
        num.sort()
        num_len = len(num)

        solutions = []
        i = 0
        while i < num_len:
            wanted = -num[i]
            j, k = i + 1, num_len - 1
            while j < k:
                two_sum = num[j] + num[k]
                if two_sum == wanted:
                    solutions.append([num[i], num[j], num[k]])
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

        return solutions


if __name__ == '__main__':
    s = Solution()

    print(s.threeSum([7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6]))
