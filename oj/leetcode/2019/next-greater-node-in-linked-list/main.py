from typing import List


class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:

    # find the closest pair with given rules -> use stack
    def nextLargerNodes(self, head: ListNode) -> List[int]:
        if head is None:
            return []

        rv = []
        stack = []
        cur_node, cur_idx = head, 0
        while cur_node is not None:
            # set current node's answer to 0
            rv.append(0)
            while True:
                if not stack:
                    # no more node pending, skip
                    break
                node, node_idx = stack[-1]
                if node.val >= cur_node.val:
                    # the top node of the stack isn't smaller than the
                    # current node, cannot remove from the stack
                    break
                # the top node of the stack is smaller than the current
                # update the top node's answer to current node
                rv[node_idx] = cur_node.val
                # ... and pop the top node from the stack
                stack.pop()

            # push current node to the pending stack
            stack.append((cur_node, cur_idx))
            cur_idx = cur_idx + 1
            cur_node = cur_node.next

        return rv


if __name__ == '__main__':
    def list_to_linked_list(l) -> ListNode:
        head = ListNode(None)
        cur = head
        for x in l:
            cur.next = ListNode(x)
            cur = cur.next
        return head.next

    s = Solution()
    print(s.nextLargerNodes(list_to_linked_list([2, 1, 5])))
    print(s.nextLargerNodes(list_to_linked_list([2, 7, 4, 3, 5])))
    print(s.nextLargerNodes(list_to_linked_list([])))
    print(s.nextLargerNodes(None))
    print(s.nextLargerNodes(list_to_linked_list([0])))
    print(s.nextLargerNodes(list_to_linked_list([0, 1])))
    print(s.nextLargerNodes(list_to_linked_list([1, 0])))
    print(s.nextLargerNodes(list_to_linked_list([3, 3])))
    print(s.nextLargerNodes(list_to_linked_list([9, 7, 6, 7, 6, 9])))
