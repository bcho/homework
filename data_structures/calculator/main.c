#include <stdio.h>
#include "calculator.h"
#include "tree.h"
#include "convert.h"

void print_formula(token_t formula[], int length);
void print_tree_node(tree_t t);

int main(int argc, char *argv[])
{
    token_t formula[MAX_OP], postfix[MAX_OP];
    int length, postfix_length;
    tree_t t;

    length = parse_formula("1+2*(3+5555)", formula);
    postfix_length = infix2postfix(formula, postfix, length);

    /* FIXME BUG tree create error
    postfix2tree(postfix, t, postfix_length);
    printf("%d\n", t->value->value);
    inorder_traversal(t, print_tree_node);
    printf("\n");
    */

    print_formula(formula, length);
    print_formula(postfix, postfix_length);

    printf("%d\n", evaluate(postfix, postfix_length));
    
    return 0;
}

void print_formula(token_t formula[], int length)
{
    int i;
    for (i = 0;i < length;i++)
        if (formula[i]->type == OPERATOR)
            printf("%c ", formula[i]->value);
        else if (formula[i]->type == OPERAND)
            printf("%d ", formula[i]->value);
    printf("\n");
}

void print_tree_node(tree_t t)
{
    if (t->value->type == OPERATOR)
        printf("%c ", t->value->value);
    else if (t->value->type == OPERAND)
        printf("%d ", t->value->value);
}
