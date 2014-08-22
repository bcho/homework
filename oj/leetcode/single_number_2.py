class Solution:
    def singleNumber(self, A):

        # Not in place.
        def three_ways_partition(num, seq):
            l, e, g = [], [], []

            for s in seq:
                if s < num:
                    l.append(s)
                elif s == num:
                    e.append(s)
                else:
                    g.append(s)

            return l, e, g

        seq = A
        while True:
            x = seq[0]
            l, e, g = three_ways_partition(x, seq)
            if len(e) == 1:
                return e[0]
            if len(l) % 3 != 0:
                seq = l
            if len(g) % 3 != 0:
                seq = g


class InPlaceSolution:
    def singleNumber(self, A):

        def three_ways_partition(num, seq):
            l, r = 0, len(seq)
            while l < r:
                if num < seq[l]:
                    r = r - 1
                    seq[l], seq[r] = seq[r], seq[l]
                else:
                    l = l + 1

            g = r

            l, r = 0, r
            while l < r:
                if num == seq[l]:
                    r = r - 1
                    seq[l], seq[r] = seq[r], seq[l]
                else:
                    l = l + 1

            return r, g

        seq = A
        while True:
            x = seq[0]
            e, g = three_ways_partition(x, seq)
            if g - e == 1:
                return seq[e]
            if e % 3 != 0:
                seq = seq[:e]
            if (len(seq) - g) % 3 != 0:
                seq = seq[g:]
