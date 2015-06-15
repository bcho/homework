class ListNode:

    def __init__(self, x, next=None):
        self.val = x
        self.next = next


class Solution:

    def mergeKLists(self, lists):

        class ListNodeHeap(object):

            INVALID = None

            def __init__(self):
                self.heap = [self.INVALID]

            def push(self, node):
                self.heap.append(node)
                self._swim(self.size)

            def pop(self):
                node = self.heap[1]
                last_node = self.heap.pop()
                if self.size:
                    self.heap[1] = last_node
                    self._sink(1)
                return node

            @property
            def is_empty(self):
                return self.size == 0

            @property
            def size(self):
                return len(self.heap) - 1

            def _cmp_node(self, a, b):
                return a.val < b.val

            def _swim(self, pos):
                while True:
                    if pos <= 1:
                        break

                    parent_node, node = self.heap[pos / 2], self.heap[pos]
                    if self._cmp_node(parent_node, node):
                        break
                    n = self.heap[pos / 2]
                    self.heap[pos / 2] = self.heap[pos]
                    self.heap[pos] = n
                    pos = pos / 2

            def _sink(self, pos):
                while pos * 2 <= self.size:
                    child_pos = pos * 2
                    if child_pos < self.size:
                        left_child = self.heap[child_pos]
                        right_child = self.heap[child_pos + 1]
                        if self._cmp_node(right_child, left_child):
                            child_pos = child_pos + 1
                    node, child = self.heap[pos], self.heap[child_pos]
                    if self._cmp_node(node, child):
                        break
                    n = self.heap[pos]
                    self.heap[pos] = self.heap[child_pos]
                    self.heap[child_pos] = n
                    pos = child_pos

        heap = ListNodeHeap()

        def insert_after(a, b):
            b.next = a.next
            a.next = b

        for l in lists:
            if l is not None:
                heap.push(l)

        sential = last_inserted = ListNode(42)
        while not heap.is_empty:
            node = heap.pop()
            if node.next is not None:
                heap.push(node.next)
            insert_after(last_inserted, node)
            last_inserted = node

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

    lists = [None]
    assert s.mergeKLists(lists) is None

    lists = [
        make_list(1, 1, 1),
        make_list(2, 2, 2)
    ]
    l = s.mergeKLists(lists)
    is_list(l, [1, 1, 1, 2, 2, 2])

    lists = [
        make_list(2, 3, 4),
        make_list(3, 4, 5),
        make_list(1, 4, 5)
    ]
    l = s.mergeKLists(lists)
    is_list(l, [1, 2, 3, 3, 4, 4, 4, 5, 5])

    lists = [
        make_list(1)
    ]
    l = s.mergeKLists(lists)
    is_list(l, [1])
