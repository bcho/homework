from typing import List


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def generateTrees(self, n: int) -> List[TreeNode]:
        if n < 1:
            return []

        memo = {}

        def as_left_sub_tree(root, child):
            root.left = child
            return root

        def as_right_sub_tree(root, child):
            root.right = child
            return root

        def F(a, b):
            if a > b:
                return [None]
            if a == b:
                return [TreeNode(a)]
            if a + 1 == b:
                return [
                    as_right_sub_tree(TreeNode(a), TreeNode(b)),
                    as_left_sub_tree(TreeNode(b), TreeNode(a)),
                ]
            memo_key = (a, b)
            if memo_key in memo:
                return memo[memo_key]

            trees = []
            for root_val in range(a, b+1):
                left_sub_trees = F(a, root_val - 1)
                right_sub_trees = F(root_val + 1, b)
                for left_sub_tree in left_sub_trees:
                    for right_sub_tree in right_sub_trees:
                        root = TreeNode(root_val)
                        root.left = left_sub_tree
                        root.right = right_sub_tree
                        trees.append(root)
            memo[memo_key] = trees
            return trees

        rv = F(1, n)
        return rv
