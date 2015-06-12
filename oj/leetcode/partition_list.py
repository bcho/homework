class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


def dump_list(head):
    node = head
    vals = []
    while node is not None:
        vals.append(node.val)
        node = node.next
    print(vals)


class Solution:

    def partition(self, head, x):

        def pop(prev):
            node = prev.next
            if not node:
                return
            prev.next = prev.next.next
            return node

        def insert_after(to, node):
            node.next = to.next
            to.next = node

        sential = ListNode(42)
        sential.next = head
        rv_sential = ListNode(42)

        last_inserted_node, prev_node = rv_sential, sential
        while prev_node is not None and prev_node.next is not None:
            if prev_node.next.val < x:
                node = pop(prev_node)
                insert_after(last_inserted_node, node)
                last_inserted_node = node
            else:
                prev_node = prev_node.next
        last_inserted_node.next = sential.next

        return rv_sential.next


if __name__ == '__main__':

    def make_list(*nums):
        sential = last_inserted = ListNode(42)
        for num in nums:
            node = ListNode(num)
            last_inserted.next = node
            last_inserted = node
        return sential.next

    def is_list(head, nums):
        node = head
        for num in nums:
            assert node is not None
            assert num == node.val
            node = node.next

    s = Solution()

    sl = make_list(1, 4, 3, 2, 5, 2)
    l = s.partition(sl, 3)
    is_list(l, [1, 2, 2, 4, 3, 5])

    sl = make_list(1, 1, 1)
    l = s.partition(sl, 3)
    is_list(l, [1, 1, 1])

    sl = make_list(4, 4, 4)
    l = s.partition(sl, 3)
    is_list(l, [4, 4, 4])
