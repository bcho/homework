class Solution:

    def rangeBitwiseAnd(self, m, n):
        changed = m ^ n
        count = 0
        while changed != 0:
            count, changed = count + 1, changed >> 1
        return m >> count << count
