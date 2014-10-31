class Solution:

    # Stackoverflow =,=
    def isBalanced(self, root):

        def balanced_and_depth(node):
            if node is None:
                return (True, 0)

            left_is_balanced, left_depth = balanced_and_depth(node.left)
            if not left_is_balanced:
                return (False, -1)
            right_is_balanced, right_depth = balanced_and_depth(node.right)
            if not right_is_balanced:
                return (False, -1)

            return (True, max(left_depth, right_depth) + 1)

        is_balanced, _ = balanced_and_depth(root)

        return is_balanced
