# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def minCameraCover(self, root: TreeNode) -> int:

        # there are 4 cases for node
        #
        #    o <- for this node, covered by children's camera
        #    |
        # o<-C->o
        covered_by_children = 0
        #
        #    C <- for this node, covered by the camera in itself
        # o<- ->o
        covered_by_itself = 1
        #
        #
        #    o <- for this node, not being covered
        not_covered = 2
        # non-node (left/right child of leave)
        none_node = 3

        camera_used = 0

        def dfs(node):
            nonlocal camera_used

            if node is None:
                return none_node
            if node.left is None and node.right is None:
                # leave is `not_covered`
                return not_covered

            left_child_mode = dfs(node.left)
            right_child_mode = dfs(node.right)

            if (left_child_mode is not_covered
                    or right_child_mode is not_covered):
                # there is at least one child has not been covered
                # so place a camera in this node
                camera_used += 1
                return covered_by_itself

            if (left_child_mode is covered_by_itself
                    or right_child_mode is covered_by_itself):
                # this node is covered by its children
                # no camera needed
                return covered_by_children

            # otherwise, not being covered
            return not_covered

        root_mode = dfs(root)
        if root_mode is not_covered:
            camera_used += 1

        return camera_used
