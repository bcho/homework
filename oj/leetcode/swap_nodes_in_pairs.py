class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


class Solution:

    def swapPairs(self, head):
        if head is None:
            return head

        get_next = lambda x: x.next if x is not None else None

        def swap(prev, a, b):
            prev.next = b
            a.next = b.next
            b.next = a

        sential = ListNode(42)
        sential.next = head
        prev, a, b = sential, head, head.next
        while a is not None and b is not None:
            na = get_next(b)
            nb = get_next(na)
            swap(prev, a, b)
            prev, a, b = a, na, nb
            if a is None or b is None:
                break

        return sential.next


if __name__ == '__main__':
    s = Solution()

    l = ListNode(1)
    sl = s.swapPairs(l)
    assert 1 == sl.val

    l = ListNode(1, ListNode(2, ListNode(3, ListNode(4))))

    sl = s.swapPairs(l)
    assert 2 == sl.val
    assert 1 == sl.next.val
    assert 4 == sl.next.next.val
    assert 3 == sl.next.next.next.val

    l = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))

    s = Solution()
    sl = s.swapPairs(l)
    assert 2 == sl.val
    assert 1 == sl.next.val
    assert 4 == sl.next.next.val
    assert 3 == sl.next.next.next.val
    assert 5 == sl.next.next.next.next.val
