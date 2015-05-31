class TrieNode:

    def __init__(self):
        self.children = {}
        self.value = None

    @property
    def is_leaf(self):
        return self.value is not None


class Trie:

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        word_len = len(word)
        i, node = 0, self.root

        while i < word_len:
            child = node.children.get(word[i])
            if not child:
                child = TrieNode()
                node.children[word[i]] = child
            node, i = child, i + 1
        node.value = word

    def search(self, word):
        word_len = len(word)
        i, node = 0, self.root

        while i < word_len:
            child = node.children.get(word[i])
            if child:
                node, i = child, i + 1
            else:
                break
        return i >= word_len and node.is_leaf

    def startsWith(self, prefix):
        prefix_len = len(prefix)
        i, node = 0, self.root

        while i < prefix_len:
            child = node.children.get(prefix[i])
            if child:
                node, i = child, i + 1
            else:
                return False
        return True  # i >= word_len


if __name__ == '__main__':
    trie = Trie()
    trie.insert('helloworld')
    assert trie.search('hello') is False
    assert trie.search('helloworld') is True
    assert trie.startsWith('hello') is True
    assert trie.startsWith('hh') is False

    trie.insert('hello')
    assert trie.search('hello') is True
