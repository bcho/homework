class Solution:

    def generate(self, rowIndex):
        row_index = rowIndex

        def factory(n):
            if n in factory.mem:
                return factory.mem[n]

            rv = n * factory(n - 1)
            factory.mem[n] = rv

            return rv

        factory.mem = {0: 1, 1: 1}

        def c(n, r):
            return factory(n) // factory(r) // factory(n - r)

        return [c(row_index, i) for i in range(0, row_index + 1)]


if __name__ == '__main__':
    s = Solution()

    print(s.generate(30))
