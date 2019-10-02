class Solution:
    def reverseParentheses(self, s: str) -> str:
        if len(s) < 1:
            return s

        stack = []
        for c in s:
            if c == '(':
                stack.append(c)
            elif c == ')':
                reversed_str = ''
                while len(stack) > 0:
                    d = stack.pop()
                    if d == '(':
                        break
                    else:
                        reversed_str += d[::-1]
                stack.append(reversed_str)
            else:
                if len(stack) == 0 or stack[-1] == '(':
                    stack.append('')
                stack[-1] += c

        rv = ''.join(stack)
        return rv
