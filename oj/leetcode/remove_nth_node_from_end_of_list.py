class ListNode:

    def __init__(self, x, n=None):
        self.val = x
        self.next = n


class Solution:

    def removeNthFromEnd(self, head, n):
        fake = ListNode(0)
        fake.next = head
        fast, slow = fake, fake

        for _ in range(n):
            fast = fast.next

        while fast is not None and fast.next is not None:
            fast = fast.next
            slow = slow.next

        if slow.next is not None:
            slow.next = slow.next.next

        return fake.next


if __name__ == '__main__':
    l = ListNode(1)

    s = Solution()
    d = s.removeNthFromEnd(l, 1)

    while d is not None:
        print(d.val)
        d = d.next
