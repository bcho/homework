class Solution:
    def singleNumber(self, A):
        # a ^ a = 0
        # 0 ^ b = b
        return reduce(lambda x, y: x ^ y, A)
