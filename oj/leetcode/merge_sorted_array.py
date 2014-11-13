class Solution:

    def merge(self, A, m, B, n):
        a_checked, b_checked = 0, 0
        c = []
        while a_checked < m and b_checked < n:
            if A[a_checked] < B[b_checked]:
                c.append(A[a_checked])
                a_checked = a_checked + 1
            else:
                c.append(B[b_checked])
                b_checked = b_checked + 1
        while a_checked < m:
            c.append(A[a_checked])
            a_checked = a_checked + 1
        while b_checked < n:
            c.append(B[b_checked])
            b_checked = b_checked + 1

        for i, x in enumerate(c):
            A[i] = x


if __name__ == '__main__':
    s = Solution()
    a, b = [1, 3, 0, 0], [2, 4]
    s.merge(a, 2, b, 2)

    print(a)
