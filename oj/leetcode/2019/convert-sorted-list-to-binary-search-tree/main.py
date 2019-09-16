class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


def print_linked_list(l: ListNode, tail=None):
    cur = l
    s = ''
    while cur is not None and cur is not tail:
        if s:
            s += '->'
        s += f'{cur.val}'
        cur = cur.next
    print(s)


class TreeNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:

    def sortedListToBST(self, head: ListNode) -> TreeNode:
        if head is None:
            return None

        def find_mid_node(
            head: ListNode,
            tail: ListNode,  # actually Optional[ListNode]
        ) -> ListNode:
            slow, fast = head, head
            while True:
                if fast is None or fast is tail or fast.next is tail:
                    return slow
                slow = slow.next
                fast = fast.next
                if fast is not None:
                    fast = fast.next

        def list_node_to_tree_node(ln: ListNode) -> TreeNode:
            return TreeNode(ln.val)

        def build_tree(
            head: ListNode,
            tail: ListNode,  # actually Optional[ListNode]
        ):
            if head is None or head is tail:
                # empty sub tree
                return None
            if head.next is tail:
                # leaf
                return list_node_to_tree_node(head)

            mid = find_mid_node(head, tail)
            assert mid is not None

            root = list_node_to_tree_node(mid)
            root.left = build_tree(head, mid)
            root.right = build_tree(mid.next, tail)
            return root

        return build_tree(head, None)


if __name__ == '__main__':
    def list_to_linked_list(l) -> ListNode:
        head = ListNode(None)
        cur = head
        for x in l:
            cur.next = ListNode(x)
            cur = cur.next
        return head.next

    def tree_to_list(t: TreeNode):
        nodes = [t]
        rv = []
        while nodes:
            node = nodes[0]
            nodes = nodes[1:]
            if node is None:
                rv.append(None)
            else:
                rv.append(node.val)
                if node.left:
                    nodes.append(node.left)
                    nodes.append(node.right)
        return rv

    s = Solution()
    rv = s.sortedListToBST(list_to_linked_list([-10, -3, 0, 5, 9]))
    print(tree_to_list(rv))
