# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def distributeCoins(self, root: TreeNode) -> int:
        move_times = 0

        def visit_tree(parent):
            nonlocal move_times

            if parent is None:
                return (0, 0)  # leaf

            left_nodes, left_coins = visit_tree(parent.left)
            right_nodes, right_coins = visit_tree(parent.right)

            # for a sub tree, we need to move |nodes - coins|
            # times to reach the distributed state, so we calculate these
            # two numbers top-down
            move_times += (abs(left_nodes - left_coins)
                           + abs(right_nodes - right_coins))
            return (
                left_nodes + right_nodes + 1,
                left_coins + right_coins + parent.val,
            )

        visit_tree(root)
        return move_times
