#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "calculator.h"
#include "tree.h"
#include "convert.h"

int infix2postfix(token_t src[], token_t dest[], int length)
{
    int front, top, tail;
    token_t stack[MAX_OP];

    for (front = 0, tail = -1, top = -1;front < length;front++) {
        if (src[front]->type == OPERAND)
            dest[++tail] = src[front];
        if (src[front]->type == OPERATOR) {
            /* ( and ) always has highest precendence */
            if (src[front]->value == '(')
                stack[++top] = src[front];
            else if (src[front]->value == ')') {
                while (stack[top]->value != '(')
                    dest[++tail] = stack[top--];
                /* pop ( */
                top--;
            } else {
                while (op_precendence(src[front]->value) <= \
                       op_precendence(stack[top]->value) && top >= 0)
                    dest[++tail] = stack[top--];
                stack[++top] = src[front];
            }
        }
    }
    while (top >= 0)
        dest[++tail] = stack[top--];
    return tail + 1;
}

void postfix2tree(token_t src[], tree_t dest, int length)
{
    tree_t stack[MAX_OP], op1, op2;
    int top, i;

    for (i = 0, top = -1;i < length;i++) {
        if (src[i]->type == OPERAND) {
            stack[++top] = build_tree_node(src[i], NULL, NULL);
        } else if (src[i]->type == OPERATOR) {
            op1 = stack[top--];
            op2 = stack[top--];
            stack[++top] = build_tree_node(src[i], op2, op1);
        }
    }
    /* top should be at the bottom (0) */
    assert(top == 0);
    dest = stack[top];
}
