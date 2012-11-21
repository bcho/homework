#include <stdlib.h>
#include <assert.h>
#include "calculator.h"

token_t new_token(TOKEN_TYPE type, int value)
{
    token_t t = malloc(sizeof(struct token_r));
    if (t == NULL)
        return NULL;
    t->type = type;
    t->value = value;
    return t;
}

void dispose_token(token_t t)
{
    free(t);
}

static int is_num(char c)
{
    return (c >= '0' && c <= '9');
}

static int is_operator(char c)
{
    char *i;
    for (i = SUPPORTEDOPERATOR;*i != '\0';i++)
        if (*i == c)
            return 1;
    return 0;
}

int parse_formula(char src[], token_t dest[])
{
    char *i;
    int tmp, found_num, j;
    for (i = src, tmp = 0, found_num = 0, j = -1;*i != '\0';i++) {
        if (is_num(*i)) {
            tmp = tmp * 10 + *i - '0';
            found_num = 1;
        } else {
            if (found_num) {
                dest[++j] = new_token(OPERAND, tmp);
                tmp = 0;
                found_num = 0;
            }
            if (is_operator(*i)) {
                dest[++j] = new_token(OPERATOR, *i);
            }
        }
    }
    if (found_num)
        dest[++j] = new_token(OPERAND, tmp);
    return j + 1;
}

OPERATOR_PRECENDENCE op_precendence(char op)
{
    switch (op) {
        case '+':
            return PLUS;
        case '-':
            return SUBTRACT;
        case '*':
            return MULTLY;
        case '/':
            return DIV;
        case '(':
        case ')':
            return PAIR;
    }
    return -1;
}

int eval(char op, int op1, int op2) {
    switch (op) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
    }
    return 0;
}

int evaluate(token_t formula[], int length)
{
    int i, top;
    int stack[MAX_OP], op1, op2;

    for (i = 0, top = -1;i < length;i++) {
        if (formula[i]->type == OPERAND) {
            stack[++top] = formula[i]->value;
        } else if (formula[i]->type == OPERATOR) {
            op1 = stack[top--];
            op2 = stack[top--];
            stack[++top] = eval(formula[i]->value, op2, op1);
        }
    }

    assert(top == 0);
    return stack[top];
}
