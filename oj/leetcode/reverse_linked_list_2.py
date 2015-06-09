class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


class Solution:

    def reverseBetween(self, head, m, n):
        if m >= n:
            return head

        def insert_after(a, b):
            b.next = a.next
            a.next = b

        sential = ListNode(42)
        sential.next = head
        node = head

        # Skipping
        counter = 1
        reverse_start = sential
        while node is not None:
            if counter >= m:
                break
            reverse_start = node
            node = node.next
            counter = counter + 1
        if reverse_start is None:
            return sential.next

        reverse_end = None
        while node is not None:
            if counter > n:
                break
            if reverse_end is None:
                reverse_end = node
            next_node = node.next
            insert_after(reverse_start, node)
            node = next_node
            counter = counter + 1
        reverse_end.next = next_node

        return sential.next


if __name__ == '__main__':
    s = Solution()

    l = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    sl = s.reverseBetween(l, 2, 4)

    assert 1 == sl.val
    assert 4 == sl.next.val
    assert 3 == sl.next.next.val
    assert 2 == sl.next.next.next.val
    assert 5 == sl.next.next.next.next.val

    l = ListNode(1, ListNode(2, ListNode(3)))
    sl = s.reverseBetween(l, 1, 3)

    assert 3 == sl.val
    assert 2 == sl.next.val
    assert 1 == sl.next.next.val

    l = ListNode(1)
    sl = s.reverseBetween(l, 1, 1)

    assert 1 == sl.val
