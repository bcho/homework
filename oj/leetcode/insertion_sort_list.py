# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

    def print_list(self):
        buf = ''
        cur_node = self
        while cur_node is not None:
            buf += str(cur_node.val) + ' '
            cur_node = cur_node.next

        return buf

    def __str__(self):
        return self.print_list()

    def __repr__(self):
        return self.print_list()

    @staticmethod
    def from_seq(seq):
        sential = ListNode(0)
        cur_node = sential
        for i in seq:
            cur_node.next = ListNode(i)
            cur_node = cur_node.next

        return sential.next


class Solution:
    # @param head, a ListNode
    # @return a ListNode
    def insertionSortList(self, head):

        def find_prev(list_head, node):
            cur_node = list_head
            while True:
                if cur_node is None:
                    raise RuntimeError('Should not reach here')

                if cur_node.next is None:
                    return cur_node

                if cur_node.next.val > node.val:
                    return cur_node

                cur_node = cur_node.next

        sential = ListNode(0)

        cur_node = head
        while cur_node is not None:
            next_node = cur_node.next
            prev_node = find_prev(sential, cur_node)
            cur_node.next = prev_node.next
            prev_node.next = cur_node

            cur_node = next_node

        return sential.next


if __name__ == '__main__':
    import random

    seq = list(range(5000))
    random.shuffle(seq)
    seq_list = ListNode.from_seq(seq)

    ListNode.print_list(seq_list)

    print(Solution().insertionSortList(seq_list))
