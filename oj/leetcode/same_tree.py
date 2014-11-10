class Solution:

    def isSameTree(self, p, q):

        def check(a, b):
            if a is None and b is None:
                return True
            if a is None and b is not None:
                return False
            if a is not None and b is None:
                return False
            if a.val != b.val:
                return False

            return check(a.left, b.left) and check(a.right, b.right)

        return check(p, q)
