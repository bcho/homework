class Solution:

    def isIsomorphic(self, s, t):

        def encode(string):
            mapping = {}
            rv = []
            for i, s in enumerate(string):
                if s in mapping:
                    rv.append(mapping[s])
                else:
                    mapping[s] = str(i)
            return ''.join(rv)

        return encode(s) == encode(t)


if __name__ == '__main__':
    s = Solution()

    assert s.isIsomorphic('egg', 'add')
    assert s.isIsomorphic('foo', 'bar') is False
    assert s.isIsomorphic('paper', 'title')
