class Solution:
    def numTrees(self, n: int) -> int:
        memo = {}

        def F(a, b):
            if a > b:
                return 1
            if a == b:
                return 1
            if a + 1 == b:
                return 2
            memo_key = (a, b)
            if memo_key in memo:
                return memo[memo_key]
            total = 0
            for idx in range(a, b+1):
                # use idx as root, there are
                #
                #   (left sub tree) * (right sub tree)
                #
                # ways to build the BST
                total += F(a, idx - 1) * F(idx + 1, b)
            # cache this sub tree's result
            memo[memo_key] = total
            return total

        return F(1, n)
