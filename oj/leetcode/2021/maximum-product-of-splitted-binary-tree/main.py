# Definition for a binary tree node.

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def maxProduct(self, root: TreeNode) -> int:
        modulo = 10 ** 9 + 7

        node_tree_sum = {}

        def count_sum(node: TreeNode):
            if node is None:
                return
            node_tree_sum[node] = node.val + count_sum(node.left) + count_sum(node.right)

        count_sum(root)

        tree_sum = node_tree_sum[root]

        def find_max_split(node: TreeNode, max_so_far: int) -> int:
            if node is None:
                return max_so_far
            if node.left is not None:
                # cut left subtree
                sub_tree_sum = node_tree_sum[node.left]
                product = sub_tree_sum * (tree_sum - sub_tree_sum)
                if product > max_so_far:
                    max_so_far = product
                max_so_far = find_max_split(node.left, max_so_far)
            if node.right is not None:
                # cut right subtree
                sub_tree_sum = node_tree_sum[node.right]
                product = sub_tree_sum * (tree_sum - sub_tree_sum)
                if product > max_so_far:
                    max_so_far = product
                max_so_far = find_max_split(node.right, max_so_far)
            return max_so_far

        return find_max_split(root) % modulo
