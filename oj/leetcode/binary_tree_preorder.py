class Solution:
    def preorderTraversal(self, root):

        def traversal(node, visited_nodes):
            if node is None:
                return

            visited_nodes.append(node.val)
            traversal(node.left, visited_nodes)
            traversal(node.right, visited_nodes)

        visited_nodes = []
        traversal(root, visited_nodes)

        return visited_nodes
