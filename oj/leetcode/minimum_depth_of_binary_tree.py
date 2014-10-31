class Solution:

    def minDepth(self, root):
        magic = 1e20

        def is_leaf(node):
            return (node is not None and
                    node.left is None and
                    node.right is None)

        def deepen(node, depth):
            if node is None:
                return magic

            if is_leaf(node):
                return depth

            return min(
                deepen(node.left, depth + 1),
                deepen(node.right, depth + 1)
            )

        return deepen(root, 1) if root is not None else 0
