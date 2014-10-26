class Solution:

    def isSymmetric(self, root):
        if root is None:
            return True

        left_q, right_q = [root.left], [root.right]

        while left_q or right_q:
            left, right = left_q.pop(), right_q.pop()
            if left is None and right is not None:
                return False
            if left is not None and right is None:
                return False
            if left is None and right is None:
                continue
            if left.val != right.val:
                return False

            left_q.append(left.left)
            left_q.append(left.right)

            right_q.append(right.right)
            right_q.append(right.left)

        if left_q or right_q:
            return False

        return True
