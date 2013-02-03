#coding: utf-8

WEIGHT = {
    'A': 2,
    'NA': 16,
    'BOOM': 1,
    'SHA': 3,
    'GET': 2,
    'YIP': 9,
    'JOB': 2,
    'WAH': 1,
}


class Node(object):
    def __init__(self, value, weight, left=None, right=None):
        self.value = value
        self.weight = weight
        self.left = left
        self.right = right

    def __eq__(self, other):
        if not self.value:
            return False
        if isinstance(other, str):
            return self.value.lower() == other.lower()
        if isinstance(other, Node):
            return self.__eq__(other.value)
        return False


class Huffman(object):
    def __init__(self, nodes):
        self._build(nodes)

    def _build(self, nodes):
        def pop_min(x):
            ret = min(x, key=lambda x: x.weight)
            x.remove(ret)
            return ret

        def encode(word, q, f):
            if f == word:
                return q
            if f.value:
                return None
            left = encode(word, q + '1', f.left)
            right = encode(word, q + '0', f.right)
            return left or right

        forest = [Node(k, v) for k, v in nodes.items()]

        while len(forest) > 1:
            right, left = pop_min(forest), pop_min(forest)
            forest.append(Node(None, left.weight + right.weight, left, right))

        self.forest = forest[0]
        self.codemap = dict([(k.lower(), encode(k, '', self.forest))
                            for k in nodes])

    def encode(self, word):
        return ''.join([self.codemap.get(i.lower(), i)
                        for i in word.split(' ')])

    def decode(self, sequence):
        def _decode(sequence, f, r):
            if f.value:
                r += ' ' + f.value
                f = self.forest
            if not sequence:
                return r
            if sequence[0] == '1':
                return _decode(sequence[1:], f.left, r)
            elif sequence[0] == '0':
                return _decode(sequence[1:], f.right, r)
            else:
                return _decode(sequence[1:], f, r)

        return _decode(sequence, self.forest, '').lstrip()

if __name__ == '__main__':
    h = Huffman(WEIGHT)
    e = h.encode('get a job')
    d = h.decode(e)
