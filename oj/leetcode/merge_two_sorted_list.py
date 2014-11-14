class ListNode:

    def __init__(self, x, n=None):
        self.val = x
        self.next = n


class Solution:

    def mergeTwoLists(self, l1, l2):
        head = ListNode(0)
        cur = head

        while l1 is not None and l2 is not None:
            if l1.val < l2.val:
                cur.next = l1
                l1 = l1.next
                cur, cur.next = cur.next, None
            else:
                cur.next = l2
                l2 = l2.next
                cur, cur.next = cur.next, None

        while l1 is not None:
            cur.next = l1
            l1 = l1.next
            cur, cur.next = cur.next, None

        while l2 is not None:
            cur.next = l2
            l2 = l2.next
            cur, cur.next = cur.next, None

        return head.next
