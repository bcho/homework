class TreeNode:

    def __init__(self, x, left=None, right=None):
        self.val = x
        self.left = left
        self.right = right


class BSTIterator:

    def __init__(self, root: TreeNode):
        self._visiting = []

        # push the left most children
        self._push_sub_tree(root)

    def next(self) -> int:
        # invariants:
        #
        # - the left sub tree already visited
        # - this call visit the node value
        # - next call visit the right sub tree
        cur = self._visiting.pop()

        self._push_sub_tree(cur.right)

        return cur.val

    def hasNext(self) -> bool:
        return len(self._visiting) > 0

    def _push_sub_tree(self, node: TreeNode):
        if node is None:
            return
        cur = node
        while True:
            if cur.left is None:
                break
            self._visiting.append(cur)
            cur = cur.left
        self._visiting.append(cur)


if __name__ == '__main__':
    root = TreeNode(
        7,
        TreeNode(3),
        TreeNode(
            15,
            TreeNode(9), TreeNode(20),
        )
    )

    iterator = BSTIterator(root)
    assert iterator.next() == 3
    assert iterator.next() == 7
    assert iterator.hasNext()
    assert iterator.next() == 9
    assert iterator.next() == 15
    assert iterator.next() == 20
    assert not iterator.hasNext()
