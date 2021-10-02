class Solution:
    
    def scoreOfStudents(self, s: str, answers: List[int]) -> int:
        
        def parse_digit(c: str) -> int:
            return ord(c) - ord('0')
        
        num_stack = []
        op_stack = []
        for idx, c in enumerate(s):
            if c == '+':
                while len(op_stack) > 0:
                    if op_stack[-1] != '*':
                        break
                    l, r = num_stack.pop(), num_stack.pop()
                    num_stack.append(l * r)
                    op_stack.pop()
                op_stack.append(c)
            elif c == '*':
                op_stack.append(c)
            else:
                num_stack.append(parse_digit(c))
        for op in op_stack[::-1]:
            l, r = num_stack.pop(), num_stack.pop()
            if op == '*':
                num_stack.append(l * r)
            else:
                num_stack.append(l + r)
        correct_answer = num_stack[0]
        
        known_answers_set = {}
        
        # calculate possible eval result in [i, j]
        # the results set between [i, j] can be cached
        def dp(i: int, j: int):
            if i == j:
                return {parse_digit(s[i])}
            if (i, j) in known_answers_set:
                return known_answers_set[(i, j)]
            
            answers_set = set()
            for m in range(i + 1, j, 2):
                for left_value in dp(i, m - 1):
                    for right_value in dp(m + 1, j):
                        if s[m] == '*':
                            answer = left_value * right_value
                        elif s[m] == '+':
                            answer = left_value + right_value
                        if answer <= 1000:
                            # avoid TLE
                            answers_set.add(answer)
                        
            known_answers_set[(i, j)] = answers_set
            return answers_set
        
        rv = []
        possibile_answers = dp(0, len(s) - 1)
        # print(possibile_answers)
        for answer_query in answers:
            if answer_query == correct_answer:
                rv.append(5)
            elif answer_query in possibile_answers:
                rv.append(2)
            else:
                rv.append(0)
        # print(answers)
        # print(rv)

        return sum(rv)