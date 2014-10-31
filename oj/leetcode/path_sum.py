class TreeNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

    def __str__(self):
        return 'Node: {0}'.format(self.val)


class Solution:

    def hasPathSum(self, root, sum):
        def is_leaf(node):
            return node.left is None and node.right is None

        def check(node, sum):
            if node is None:
                return False

            if is_leaf(node):
                return sum == node.val

            remains = sum - node.val
            has_path = False
            if node.left:
                has_path = has_path or check(node.left, remains)
            if has_path:
                return True

            if node.right:
                has_path = has_path or check(node.right, remains)
            return has_path

        return check(root, sum)


if __name__ == '__main__':
    t = TreeNode(7)
    t1 = TreeNode(0)
    t.left = t1
    t1 = TreeNode(-1)
    t.left.left = t1
    t1 = TreeNode(-6)
    t.left.right = t1
    t1 = TreeNode(1)
    t.left.left.right = t1
    t1 = TreeNode(-7)
    t.left.left.right.left = t1

    s = Solution()

    print(s.hasPathSum(t, 0))
