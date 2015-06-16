class Solution:

    def isHappy(self, n):
        cal = lambda num: sum(i ** 2 for i in str(num))

        found = {n: True}
        while True:
            next_n = cal(n)
            if next_n == 1:
                return True
            if next_n in found:
                return False
            found[next_n] = True
            n = next_n
