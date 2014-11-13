class ListNode:

    def __init__(self, x, n=None):
        self.val = x
        self.next = n


class Solution:

    def deleteDuplicates(self, head):
        sential = ListNode(-1 << 30)

        last_node, cur_node = sential, head
        while cur_node is not None:
            next_node = cur_node.next
            if cur_node.val != last_node.val:
                last_node.next = cur_node
                last_node = cur_node
                last_node.next = None
            cur_node = next_node

        return sential.next


if __name__ == '__main__':
    l = ListNode(0)

    s = Solution()
    d = s.deleteDuplicates(l)
    while d is not None:
        print(d.val)
        d = d.next
