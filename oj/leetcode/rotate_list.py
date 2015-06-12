class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


class Solution:

    def rotateRight(self, head, k):
        if not head or k <= 0:
            return head

        def get_length(node):
            length = 0
            while node is not None:
                length = length + 1
                node = node.next
            return length

        length = get_length(head)
        k = k % length

        slow, fast = head, head

        while k > 0:
            fast, k = fast.next, k - 1

        while fast and fast.next:
            slow, fast = slow.next, fast.next

        fast.next = head
        head = slow.next
        slow.next = None

        return head


if __name__ == '__main__':
    s = Solution()

    sl = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    l = s.rotateRight(sl, 2)
    assert 4 == l.val
    assert 5 == l.next.val
    assert 1 == l.next.next.val
    assert 2 == l.next.next.next.val
    assert 3 == l.next.next.next.next.val

    sl = ListNode(1)
    l = s.rotateRight(sl, 1)
    assert 1 == l.val

    assert s.rotateRight(None, 1) is None
