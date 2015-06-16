class Solution:

    def findRepeatedDnaSequences(self, s):

        def encode(seq):
            rv = 0
            mapping = {'A': 0, 'C': 1, 'G': 2, 'T': 3}
            for i in seq:
                rv = rv * 4 + mapping[i.upper()]
            return rv

        rv, encoded_seq = [], {}
        for i in range(len(s) - 9):
            seq = s[i:i + 10]
            encoded = encode(seq)
            found_times = encoded_seq.get(encoded, 0)
            if found_times == 1:
                rv.append(seq)
            encoded_seq[encoded] = found_times + 1
        return rv


if __name__ == '__main__':
    s = Solution()

    rv = s.findRepeatedDnaSequences('AAAAAAAAAAAA')
    assert 'AAAAAAAAAA' == rv[0]
    assert 1 == len(rv)

    rv = s.findRepeatedDnaSequences('AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT')
    assert 'AAAAACCCCC' in rv
    assert 'CCCCCAAAAA' in rv
