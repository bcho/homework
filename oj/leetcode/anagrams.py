class Solution:

    def anagrams(self, strs):
        if not strs or len(strs) == 1:
            return []

        def encode(string):
            ab_map = {}
            for s in string:
                if s not in ab_map:
                    ab_map[s] = 0
                ab_map[s] = ab_map[s] + 1
            ab = sorted(ab_map.keys())
            d = lambda a: '{0}:{1}'.format(a, ab_map[a])
            return ''.join(map(d, ab))

        groups = {}
        for string in strs:
            encoded = encode(string)
            if encoded not in groups:
                groups[encoded] = []
            groups[encoded].append(string)
        rv = []
        for group in groups.values():
            if len(group) > 1:
                rv = rv + group
        return rv


if __name__ == '__main__':
    s = Solution()

    assert 0 == len(s.anagrams(['ab']))
    assert 2 == len(s.anagrams(['ab', 'ba']))
    assert 2 == len(s.anagrams(['a', 'a']))
    assert 0 == len(s.anagrams(['ab', 'abb']))
