from typing import List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self):
        return f'val=({self.val}), left=({self.left}), right=({self.right})'


class Solution:

    def removeLeafNodes(self, root: TreeNode, target: int) -> TreeNode:
        print(root)
        pseudo_root = TreeNode(val=None)
        pseudo_root.left = root

        child_to_parent = {}
        leaf_nodes = []

        def build_child_to_parent_index(n: TreeNode):
            if n is None:
                return
            has_children = False
            if n.left is not None:
                child_to_parent[n.left] = n
                build_child_to_parent_index(n.left)
                has_children = True
            if n.right is not None:
                child_to_parent[n.right] = n
                build_child_to_parent_index(n.right)
                has_children = True
            if not has_children:
                leaf_nodes.append(n)

        build_child_to_parent_index(root)

        while len(leaf_nodes) > 0:
            leaf_node, leaf_nodes = leaf_nodes[0], leaf_nodes[1:]
            if leaf_node.val != target:
                # no need to remove
                continue
            # remove and update index
            parent_node = child_to_parent.get(leaf_node)
            if not parent_node:
                continue
            if parent_node.left == leaf_node:
                parent_node.left = None
            if parent_node.right == leaf_node:
                parent_node.right = None
            if parent_node.left is None and parent_node.right is None:
                leaf_nodes.append(parent_node)

        return pseudo_root.left


def array_to_tree_node(a: List[int]) -> TreeNode:
    nodes = []
    for val in a:
        if val is None:
            nodes.append(val)
        else:
            nodes.append(TreeNode(val))
    for idx, node in enumerate(nodes):
        left_child_idx = 2 * idx + 1
        if left_child_idx < len(nodes):
            node.left = nodes[left_child_idx]
        right_child_idx = 2 * idx + 2
        if right_child_idx < len(nodes):
            node.right = nodes[right_child_idx]

    return nodes[0]


def tree_node_to_array(a: TreeNode) -> List[int]:
    rv = []
    items = [a]
    while len(items) > 0:
        item, items = items[0], items[1:]
        if item is None:
            rv.append(None)
        else:
            rv.append(item.val)
            if item.left is not None or item.right is not None:
                items.append(item.left)
                items.append(item.right)

    return rv


if __name__ == '__main__':
    s = Solution()

    v = s.removeLeafNodes(
        array_to_tree_node([1, 2, 3, 2, None, 2, 4]),
        2,
    )
    print(tree_node_to_array(v))
    assert tree_node_to_array(v) == [1, None, 3, None, 4]

    v = s.removeLeafNodes(
        array_to_tree_node([1, 3, 3, 3, 2]),
        3,
    )
    print(tree_node_to_array(v))
    assert tree_node_to_array(v) == [1, 3, None, None, 2]

    v = s.removeLeafNodes(
        array_to_tree_node([1, 2, None, 2, None, 2]),
        2,
    )
    print(tree_node_to_array(v))
    assert tree_node_to_array(v) == [2]

    v = s.removeLeafNodes(
        array_to_tree_node([1, 1, 1]),
        1,
    )
    print(tree_node_to_array(v))
    assert tree_node_to_array(v) == []

    v = s.removeLeafNodes(
        array_to_tree_node([1, 2, 3]),
        1,
    )
    print(tree_node_to_array(v))
    assert tree_node_to_array(v) == [1, 2, 3]
