class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


class Solution:

    def removeElements(self, head, val):
        sential = ListNode(42)
        sential.next = head

        prev_node, cur_node = sential, head
        while cur_node is not None:
            if cur_node.val == val:
                prev_node.next = cur_node.next
            else:
                prev_node = cur_node
            cur_node = cur_node.next

        return sential.next


if __name__ == '__main__':
    s = Solution()

    def make_list(*nums):
        sential = ListNode(42)
        last = sential
        for num in nums:
            node = ListNode(num)
            last.next = node
            last = node
        return sential.next

    l = make_list(1, 2, 6, 3, 4, 5, 6)
    sl = s.removeElements(l, 6)
    assert 1 == sl.val
    assert 2 == sl.next.val
    assert 3 == sl.next.next.val
    assert 4 == sl.next.next.next.val
    assert 5 == sl.next.next.next.next.val

    l = make_list(1, 2, 3)
    sl = s.removeElements(l, 6)
    assert 1 == sl.val
    assert 2 == sl.next.val
    assert 3 == sl.next.next.val
