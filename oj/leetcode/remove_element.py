class Solution:

    def removeElement(self, A, elem):
        counter, i, a_length = -1, 0, len(A)

        while i < a_length:
            if A[i] != elem:
                counter = counter + 1
                A[counter] = A[i]
            i = i + 1

        return counter + 1


if __name__ == '__main__':
    s = Solution()

    a = [1, 2, 2, 2]
    print(s.removeElement(a, 1), a)

    a = [1, 1, 1, 1]
    print(s.removeElement(a, 1), a)

    a = [1, 2, 2, 2]
    print(s.removeElement(a, 2), a)
