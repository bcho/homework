class Solution:
    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        class Node:
            
            @classmethod
            def build(cls, word: str):
                if word == '':
                    return None
                node = cls(word[0])
                if len(word) == 1:
                    node.is_terminal = True
                    return node
                next_node = cls.build(word[1:])
                if next_node is not None:
                    node.add_next_node(next_node)
                return node
            
            def __init__(self, value: str):
                self.value = value
                self.next_nodes = {}
                self.is_terminal = False
                
            def __str__(self):
                next_node_values = '/'.join(self.next_nodes.keys())
                return f'value={self.value}, next_nodes={next_node_values}'
                
            def __repr__(self):
                return self.__str__()
                
            def add_next_node(self, next_node):
                if next_node.value not in self.next_nodes:
                    self.next_nodes[next_node.value] = next_node
                    return
                self.next_nodes[next_node.value].merge(next_node)
                
            def merge(self, other):
                # merge merges two nodes together
                if other.is_terminal:
                    self.is_terminal = True
                for next_node in other.next_nodes.values():
                    self.add_next_node(next_node)
                
            def match_shortest_prefix(self, word: str):
                # match_shortest_prefix finds the shortest prefix starts from current character. It returns None if no prefix found
                if word == '':
                    return ''
                if word[0] != self.value:
                    return None
                if len(word) == 0:
                    return self.value
                if self.is_terminal:
                    return self.value
                matched_any = False
                shortest_prefix = word
                for next_node in self.next_nodes.values():
                    next_node_prefix = next_node.match_shortest_prefix(word[1:])
                    if next_node_prefix is None:
                        continue
                    matched_any = True
                    if len(next_node_prefix) < len(shortest_prefix):
                        shortest_prefix = next_node_prefix
                if not matched_any:
                    return None
                return self.value + shortest_prefix
        
        
        trees = {}
        for word in dictionary:
            node = Node.build(word)
            if node.value in trees:
                print(f'merge {trees[node.value]} with {node}')
                trees[node.value].merge(node)
            else:
                trees[node.value] = node
                
        print(trees)
                
        rv = []
        for word in sentence.split(' '):
            c = word[0]
            matched = False
            if c in trees:
                prefix = trees[c].match_shortest_prefix(word)
                print(f'word: {word}, prefix: {prefix}')
                if prefix is not None:
                    matched = True
                    rv.append(prefix)
            if not matched:
                print(f'word: {word}, no match')
                rv.append(word)
                
        return ' '.join(rv)