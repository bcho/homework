class Solution:

    def plusOne(self, digits):
        i = len(digits) - 1
        base = 10

        digits[i] = digits[i] + 1
        while i >= 1:
            if digits[i] >= base:
                digits[i - 1] = digits[i] // base + digits[i - 1]
                digits[i] = digits[i] % base
            i = i - 1
        if digits[0] >= base:
            digits.insert(0, digits[0] // base)
            digits[1] = digits[1] % base

        return digits


if __name__ == '__main__':
    s = Solution()

    print(s.plusOne([8, 9, 9]))
