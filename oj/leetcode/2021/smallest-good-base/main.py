class Solution:

    def smallestGoodBase(self, n: str) -> str:

        def binary_search_k(q: int):
            left = 2
            right = int(pow(n, 1/(q - 1))) + 1
            while True:
                if left > right:
                    return None
                k = (right + left) // 2
                sum, kk = 0, 1
                for i in range(0, q):
                    sum += kk
                    kk *= k
                if sum == n:
                    return k
                elif sum > n:
                    right = k - 1
                elif sum < n:
                    left = k + 1

        n = int(n)
        for q in range(60, 1, -1):
            k = binary_search_k(q)
            if k is not None:
                return str(k)

        return str(n - 1)


if __name__ == '__main__':
    s = Solution()

    assert s.smallestGoodBase('13') == '3'
    assert s.smallestGoodBase('4681') == '8'
    assert s.smallestGoodBase('1000000000000000000') == '999999999999999999'
    assert s.smallestGoodBase("2251799813685247") == '2'
