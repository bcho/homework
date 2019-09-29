from typing import List


# Definition for a binary tree node.

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def delNodes(self, root: TreeNode, to_delete: List[int]) -> List[TreeNode]:

        to_delete = set(to_delete)
        node_idx = {}
        rv = []

        def visit(node, idx):
            if node is None:
                return

            parent_idx = (idx - 1) // 2
            parent = None
            if parent_idx >= 0:
                parent = node_idx[parent_idx]

            node_idx[idx] = node
            if node.val in to_delete:
                if parent is not None:
                    # delete node from parent
                    if parent_idx * 2 + 1 == idx:
                        parent.left = None
                    else:
                        parent.right = None
                # delete node from index
                node_idx[idx] = None
            else:
                if parent is None:
                    # no parent, add as new tree
                    rv.append(node)

            visit(node.left, 2 * idx + 1)
            visit(node.right, 2 * idx + 2)

        visit(root, 0)

        return rv
