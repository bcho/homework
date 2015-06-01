class Solution:

    def permute(self, nums):

        def d(picked, p, pickables):
            if not pickables:
                picked.append([i for i in p])

            for ip, pickable in enumerate(pickables):
                p.append(pickable)
                next_pickables = [c for ic, c in enumerate(pickables)
                                  if ic != ip]
                d(picked, p, next_pickables)
                p.pop()

        x = []
        d(x, [], nums)

        return x


if __name__ == '__main__':
    s = Solution()
    print(len(s.permute([i for i in range(8)])))
