class Solution:

    def levelOrder(self, root):
        q, levels = [(root, 1)], []
        while q:
            (node, depth) = q.pop(0)
            if node is None:
                continue

            if len(levels) < depth:
                levels.append([])

            levels[depth - 1].append(node.val)

            q.append((node.left, depth + 1))
            q.append((node.right, depth + 1))

        return levels
