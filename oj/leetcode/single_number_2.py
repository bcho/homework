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


class CountBitsSolution:

    def singleNumber(self, A):
        bits = [0] * 32
        for num in A:
            for bit_idx in range(32):
                bits[bit_idx] += num & (1 << bit_idx)

        rv = 0
        for bit_idx, bit_count in enumerate(bits):
            if bit_count % 3 > 0:
                rv |= 1 << bit_idx
        if bits[-1] % 3 > 0:
            # negative number
            rv = rv - (1 << 32)
        return rv


class CircuitSolution:

    def singleNumber(self, A):
        a, b = 0, 0
        for num in A:
            na = (~a & b & num) | (a & ~b & ~num)
            b = (~a & ~b & num) | (~a & b & ~num)
            a = na
        return b
