class TreeNode:

    def __init__(self, x, l=None, r=None):
        self.val = x
        self.left = l
        self.right = r


class Solution:

    def pathSum(self, root, sum):

        found = []

        def dfs(cur, previous, remains):
            if cur is None:
                return

            remains = remains - cur.val
            if cur.left is None and cur.right is None:
                if remains == 0:
                    previous.append(cur)
                    found.append([i.val for i in previous])
                return

            dfs(cur.left, previous + [cur], remains)
            dfs(cur.right, previous + [cur], remains)

        dfs(root, [], sum)

        return found


if __name__ == '__main__':
    s = Solution()

    print(s.pathSum(TreeNode(0, TreeNode(2, TreeNode(3)), TreeNode(5)), 5))
