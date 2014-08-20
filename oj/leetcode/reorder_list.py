class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def reorderList(self, head):

        def reverse(root):
            sential = ListNode(0)
            node = root

            while node is not None:
                next_node = node.next
                node.next = sential.next
                sential.next = node

                node = next_node

            return sential.next

        def find_mid(root):
            slow = root
            fast = root

            while fast is not None and fast.next is not None:
                slow = slow.next
                fast = fast.next.next

            return slow

        part_a, part_b = head, None
        part_a_last = find_mid(head)
        if part_a_last is not None:
            part_b = part_a_last.next
            part_a_last.next = None

        part_b = reverse(part_b)

        sential = ListNode(0)
        cur_node = sential

        while part_a is not None and part_b is not None:
            cur_node.next = part_a
            part_a = part_a.next
            cur_node = cur_node.next

            cur_node.next = part_b
            part_b = part_b.next
            cur_node = cur_node.next

        while part_a is not None:
            cur_node.next = part_a
            part_a = part_a.next
            cur_node = cur_node.next

        while part_b is not None:
            cur_node.next = part_b
            part_b = part_b.next
            cur_node = cur_node.next

        return sential.next
