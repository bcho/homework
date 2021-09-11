class Solution:
    def minTime(self, n: int, edges: List[List[int]], hasApple: List[bool]) -> int:
        # make sure we have stable edge travesal order
        edges = sorted(edges, key=lambda x: x[0])

        node_children = {}
        node_parent = {}
        for e0, e1 in edges:
            # handle special case:
            # the node with smaller idx is the child node of the node with bigger index
            if e1 in node_parent:
                e0, e1 = e1, e0
            if e0 not in node_children:
                node_children[e0] = set()
            node_children[e0].add(e1)
            node_parent[e1] = e0

        _node_has_apples = {node: h for node, h in enumerate(hasApple)}
        def node_has_apples(node: int) -> int:
            if _node_has_apples[node]:
                return True
            child_nodes = node_children.get(node)
            if not child_nodes:
                return False
            _node_has_apples[node] = any(
                node_has_apples(child_node)
                for child_node in child_nodes
            )
            return _node_has_apples[node]

        # build the cache
        node_has_apples(0)

        # print('node_has_apples', _node_has_apples)
        # print('node_children', node_children)
        # print('node_parent', node_parent)

        def walk_times_for_node(node: int) -> int:
            if not node_has_apples(node):
                # no need to walk this node and its children
                return 0
            child_nodes = node_children.get(node)
            if not child_nodes:
                # no need to walk the children
                return 0
            walk_times = 0
            for child_node in child_nodes:
                if not node_has_apples(child_node):
                    # no need to walk
                    continue
                # 2 is the time for walking back to current node
                walk_times += 2 + walk_times_for_node(child_node)
            return walk_times

        return walk_times_for_node(0)
