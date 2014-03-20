#include "binary_expression.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_SIZE 1000
#define NO_ANSWER -(1 << 30)


int op_compare(char a, char b)
{
#define TEST(_a, _b, r) if (a == _a && b == _b) return (r)

    TEST('+', '+', 1); TEST('+', '-', 1); TEST('+', '*', -1); TEST('+', '/', -1); TEST('+', '(', 1); TEST('+', ')', 0);
    TEST('-', '+', 1); TEST('-', '-', 1); TEST('-', '*', -1); TEST('-', '/', -1); TEST('-', '(', 1); TEST('-', ')', 0);
    TEST('*', '+', 1); TEST('*', '-', 1); TEST('*', '*', 1); TEST('*', '/', 1); TEST('*', '(', 1); TEST('*', ')', 0);
    TEST('/', '+', 1); TEST('/', '-', 1); TEST('/', '*', 1); TEST('/', '/', 1); TEST('/', '(', 1); TEST('/', ')', 0);
    TEST('(', '+', 1); TEST('(', '-', 1); TEST('(', '*', 1); TEST('(', '/', 1); TEST('(', '(', 1); TEST('(', ')', 0);
    TEST(')', '+', -1); TEST(')', '-', -1); TEST(')', '*', -1); TEST(')', '/', -1); TEST(')', '(', 0); TEST(')', ')', -1);

    return 1;

#undef TEST
}

int op_calculate(char op, int a, int b)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;

    return NO_ANSWER;
}

int is_op(char a)
{
    return (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')');
}

int calculate(char *expression)
{
    int nums[MAX_SIZE];
    char ops[MAX_SIZE];
    int nums_top, ops_top;
    char num[11];
    char *c;
    char op_prev;
    int a, b;

    num[0] = 0;
    nums_top = -1;
    ops_top = -1;
    for (c = expression; *c != '\0';) {
        if (is_op(*c)) {
            if (strlen(num) != 0) {
                nums_top = nums_top + 1;
                nums[nums_top] = atoi(num);
                num[0] = 0;
            }

            op_prev = ops[ops_top];
            if (ops_top < 0 || op_compare(*c, op_prev) > 0) {
                ops_top = ops_top + 1;
                ops[ops_top] = *c;
                c = c + 1;
            } else if (op_compare(*c, op_prev) == 0) {
                ops_top = ops_top - 1;
                c = c + 1;
            } else if (op_compare(*c, op_prev) < 0) {
                b = nums[nums_top];
                nums_top = nums_top - 1;
                a = nums[nums_top];
                nums[nums_top] = op_calculate(op_prev, a, b);

                ops_top = ops_top - 1;
            }
        } else if (isalnum(*c)) {
            sprintf(num, "%s%c", num, *c);
            c = c + 1;
        } else {
            c = c + 1;
        }
    }
    if (strlen(num) != 0) {
        nums_top = nums_top + 1;
        nums[nums_top] = atoi(num);
    }
    
    while (ops_top != -1) {
        op_prev = ops[ops_top];
        ops_top = ops_top - 1;
        b = nums[nums_top];
        nums_top = nums_top - 1;
        a = nums[nums_top];
        nums[nums_top] = op_calculate(op_prev, a, b);
    }

    return nums[0];
}
