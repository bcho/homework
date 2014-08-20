class Solution:
    def postorderTraversal(self, root):

        def traversal(node, visited_list):
            if node is None:
                return

            traversal(node.left, visited_list)
            traversal(node.right, visited_list)

            visited_list.append(node.val)

        rv = []
        traversal(root, rv)

        return rv
