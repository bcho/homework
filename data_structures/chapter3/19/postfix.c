#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "postfix.h"

#define PRECIS 20

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int is_op(char c)
{
    return (c == '*' || c == '/' \
            || c == '+' || c == '-');
}

static void eval(char op, stack_t s)
{
    element_t operand[2];
    operand[1] = top(s); pop(s);
    operand[0] = top(s); pop(s);
    switch(op) {
        case '*':
            push(operand[0] * operand[1], s);
            break;
        case '/':
            push(operand[0] / operand[1], s);
            break;
        case '+':
            push(operand[0] + operand[1], s);
            break;
        case '-':
            push(operand[0] - operand[1], s);
            break;
    }
}

element_t evaluate(char *formula)
{
    stack_t s = create_stack(MAX_OP);
    char *start, *i;

    i = formula;
    start = NULL;
    while (*i != '\0') {
        if (is_digit(*i) && !start) {
            start = i;
        } else if (is_op(*i)) {
            eval(*i, s);
        } else {
            if (start != NULL) {
                push((element_t) strtol(start, &i, 10), s);
                start = NULL;
            }
        }
        i++;
    }
    if (s->top == 0)
        return top(s);
    else
        return -1;
}
