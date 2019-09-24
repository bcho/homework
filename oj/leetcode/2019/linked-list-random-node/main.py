# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
import random

class Solution:

    def __init__(self, head: ListNode):
        """
        @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node.
        """
        self.head = head

    def getRandom(self) -> int:
        """
        Returns a random node's value.
        """
        cur = self.head
        pool = []
        while len(pool) < 1:
            # build the pool
            pool.append(cur.val)
            cur = cur.next

        i = 1
        while cur is not None:
            poss = random.random()
            if poss <= len(pool) / (len(pool) + i):
                replace_position = random.randint(0, len(pool) - 1)
                pool[replace_position] = cur.val
            i = i + 1
            cur = cur.next

        return pool[0]


# Your Solution object will be instantiated and called as such:
# obj = Solution(head)
# param_1 = obj.getRandom()<Paste>
