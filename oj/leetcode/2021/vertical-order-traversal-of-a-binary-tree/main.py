# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def verticalTraversal(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root is None:
            return []

        column_to_nodes = {}
        minimum_column = 1e10
        maximum_column = -1e10

        def mark_node_column(column: int, row: int, node: TreeNode):
            nonlocal minimum_column
            nonlocal maximum_column
            if column < minimum_column:
                minimum_column = column
            if column > maximum_column:
                maximum_column = column
            if column not in column_to_nodes:
                column_to_nodes[column] = []
            column_to_nodes[column].append((row, node.val))
            if node.left is not None:
                mark_node_column(column - 1, row + 1, node.left)
            if node.right is not None:
                mark_node_column(column + 1, row + 1, node.right)

        mark_node_column(0, 0, root)

        print('minimum_column,maximum_column', minimum_column, maximum_column)
        rv = []
        for column in range(minimum_column, maximum_column + 1):
            if column not in column_to_nodes:
                continue
            nodes = [
                x[1]
                for x in sorted(column_to_nodes[column])
            ]
            rv.append(nodes)

        return rv
