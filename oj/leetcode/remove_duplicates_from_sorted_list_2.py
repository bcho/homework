class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


class Solution:

    def deleteDuplicates(self, head):

        def peek(node):
            if node is None:
                return None
            next_node = node.next
            if next_node is None:
                return None
            return next_node.val

        def skip_to_new_val(prev_node, node, val):
            while node is not None and node.val == val:
                node = node.next
            prev_node.next = node

        sential = prev_node = ListNode(42)
        sential.next = head

        node = head
        while node is not None:
            if peek(node) == node.val:
                skip_to_new_val(prev_node, node, node.val)
            else:
                prev_node = node
            node = prev_node.next

        return sential.next


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

    sl = make_list(1, 2, 3, 3, 4, 4, 5)
    l = s.deleteDuplicates(sl)
    is_list(l, [1, 2, 5])

    sl = make_list(1, 1, 1, 2, 3)
    l = s.deleteDuplicates(sl)
    is_list(l, [2, 3])

    sl = make_list(1, 2, 3)
    l = s.deleteDuplicates(sl)
    is_list(l, [1, 2, 3])

    assert s.deleteDuplicates(None) is None
