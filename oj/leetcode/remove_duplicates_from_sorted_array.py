class Solution:

    def removeDuplicates(self, A):
        length, counter = 0, 1
        a_length = len(A)

        if a_length < 1:
            return 0

        while counter < a_length:
            if A[counter] != A[length]:
                length = length + 1
                A[length] = A[counter]
            counter = counter + 1

        return length + 1


if __name__ == '__main__':
    s = Solution()

    a = []
    print(s.removeDuplicates(a), a)

    a = [1, 1, 2]
    print(s.removeDuplicates(a), a)

    a = [1, 2]
    print(s.removeDuplicates(a), a)
