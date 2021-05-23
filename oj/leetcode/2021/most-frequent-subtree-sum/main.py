import collections
from typing import List


class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def findFrequentTreeSum(self, root: TreeNode) -> List[int]:
        recorded = collections.defaultdict(int)

        def visit(n):
            if n is None:
                return 0
            x = n.val + visit(n.left) + visit(n.right)
            recorded[x] += 1
            return x

        visit(root)

        subtree_sum_freqs = collections.defaultdict(list)
        max_times = -1
        for subtree_sum, times in recorded.items():
            if times > max_times:
                max_times = times
            subtree_sum_freqs[times].append(subtree_sum)

        return subtree_sum_freqs[max_times]


if __name__ == '__main__':
    s = Solution()

    assert sorted(s.findFrequentTreeSum(
        TreeNode(
            5,
            left=TreeNode(2),
            right=TreeNode(-3),
        )
    )) == sorted([2, -3, 4])

    assert sorted(s.findFrequentTreeSum(
        TreeNode(
            5,
            left=TreeNode(2),
            right=TreeNode(-5),
        )
    )) == sorted([2])
