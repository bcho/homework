class Solution:

    def isValid(self, s):
        push_set = set('({[')
        pop_set = set(')}]')
        pairs = {')': '(', ']': '[', '}': '{'}

        stack = []
        for symbol in s:
            if symbol in push_set:
                stack.append(symbol)
            elif symbol in pop_set:
                try:
                    top = stack.pop()
                except Exception:
                    return False
                if top != pairs[symbol]:
                    return False

        return len(stack) == 0


if __name__ == '__main__':
    s = Solution()
    print(s.isValid('('))
    print(s.isValid('()'))
    print(s.isValid('([])'))
    print(s.isValid('()[]{}'))
    print(s.isValid('(]'))
    print(s.isValid('([)]'))
