class ListNode:

    def __init__(self, x, n=None):
        self.val = x
        self.next = n


class Solution:

    def addTwoNumbers(self, l1, l2):
        base = 10
        sum = ListNode(0)

        a, b, c, carry = l1, l2, sum, 0
        while a is not None and b is not None:
            c.next = ListNode(a.val + b.val + carry)
            a, b, c = a.next, b.next, c.next
            carry, c.val = c.val // base, c.val % base

        while a is not None:
            c.next = ListNode(a.val + carry)
            a, c = a.next, c.next
            carry, c.val = c.val // base, c.val % base

        while b is not None:
            c.next = ListNode(b.val + carry)
            b, c = b.next, c.next
            carry, c.val = c.val // base, c.val % base

        while carry > 0:
            c.next, carry = ListNode(carry % base), carry // base
            c = c.next

        return sum.next


if __name__ == '__main__':
    s = Solution()
    t = s.addTwoNumbers(ListNode(8), ListNode(2))

    while t is not None:
        print(t.val)
        t = t.next
