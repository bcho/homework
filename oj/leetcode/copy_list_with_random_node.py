class RandomListNode:
    def __init__(self, x):
        self.label = x
        self.next = None
        self.random = None


class Solution:
    def copyRandomList(self, head):

        def copy_a_node(node):
            new_node = RandomListNode(node.label)

            return new_node

        signature = {}

        sential = RandomListNode(0)
        cur_node = head
        copy_node = sential
        while cur_node is not None:
            new_node = copy_a_node(cur_node)
            copy_node.next = new_node

            signature[hash(cur_node)] = new_node

            cur_node = cur_node.next
            copy_node = copy_node.next

        copy_node = sential.next
        cur_node = head
        while cur_node is not None:
            random_node = signature.get(hash(cur_node.random))
            copy_node.random = random_node

            cur_node = cur_node.next
            copy_node = copy_node.next

        return sential.next
