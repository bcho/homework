class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


class Solution:

    def reverseList(self, head):

        def insert_after(a, b):
            b.next = a.next
            a.next = b

        sential = ListNode(42)
        node = head
        while node is not None:
            next_node = node.next
            insert_after(sential, node)
            node = next_node

        return sential.next


if __name__ == '__main__':
    s = Solution()

    l = ListNode(1, ListNode(2, ListNode(3)))
    sl = s.reverseList(l)

    assert 3 == sl.val
    assert 2 == sl.next.val
    assert 1 == sl.next.next.val

    l = ListNode(1)
    sl = s.reverseList(l)

    assert 1 == sl.val
