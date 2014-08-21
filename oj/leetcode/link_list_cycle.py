class ListNode:
    pass


class Solution:
    def detectCycle(self, head):

        def detect_cycle(start_node):
            slow, fast = start_node, start_node

            if fast is not None:
                fast = fast.next

            while slow != fast and fast is not None and fast.next is not None:
                slow = slow.next
                fast = fast.next.next

            return slow == fast and fast is not None, fast

        def mark_cycle(start_node):
            cycle_nodes = set([start_node])
            cur_node = start_node.next
            while cur_node is not None and start_node != cur_node:
                cycle_nodes.add(cur_node)
                cur_node = cur_node.next

            return cycle_nodes

        def find_cycle_start(start_node, cycle_nodes):
            sential = ListNode(0)
            sential.next = start_node
            cur_node = sential

            while cur_node is not None and cur_node.next not in cycle_nodes:
                cur_node = cur_node.next

            return cur_node.next

        has_cycle, meeting_node = detect_cycle(head)

        # No cycle.
        if not has_cycle:
            return None

        nodes_in_cycle = mark_cycle(meeting_node)
        return find_cycle_start(head, nodes_in_cycle)
