#include "lexpr.h"

/* ops */
#define Negation '~'
#define Conjunction '+'
#define Disjunction '*'
#define Implication '-'
#define Equivalence '='
#define LeftParenthesis '('
#define RightParenthesis ')'

#define STACK_SIZE 200


int op_level(char op)
{
    if (op == Equivalence)
        return 0;
    if (op == Implication)
        return 1;
    if (op == Conjunction)
        return 2;
    if (op == Disjunction)
        return 3;
    if (op == Negation)
        return 4;
    if (op == LeftParenthesis || op == RightParenthesis)
        return 5;

    return -1;
}

int is_op(char x)
{
    return (x == Equivalence || x == Implication || x == Conjunction || \
            x == Disjunction || x == Disjunction || x == Negation || \
            x == LeftParenthesis || x == RightParenthesis);
}

int is_whitespace(char x)
{
    return x == ' ';
}

int is_value(char x)
{
    return (x >= 'A' && x <= 'Z');
}

int is_bino_op(char x)
{
    return is_op(x) && (x == Conjunction || x == Disjunction || \
                        x == Implication || x == Equivalence);
}

int validate_lexpr(char *formula)
{
    char x, op;
    int vt, opt, level;
    char ops[STACK_SIZE];

    vt = -1; opt = -1;
    while ((x = *formula++) != '\0')
        if (is_value(x)) {
            vt += 1;
        } else if (is_op(x)) {
            level = op_level(x);
            while (opt >= 0 && level < op_level(ops[opt]) && \
                    ops[opt] != LeftParenthesis) {
                op = ops[opt];
                opt -= 1;
                if (is_bino_op(op))
                    vt -= 1;
                if (vt < 0)
                    return 0;
            }
            if (x == RightParenthesis) {
                while (opt >=0 && ops[opt] != LeftParenthesis) {
                    op = ops[opt];
                    if (is_bino_op(op))
                        vt -= 1;
                    if (vt < 0)
                        return 0;
                    opt -= 1;
                }
                if (opt < 0)
                    return 0;
                opt -= 1;
            } else {
                ops[++opt] = x;
            }
        } else if (!is_whitespace(x)){
            return 0;
        }

    while (opt >= 0) {
        op = ops[opt];
        if (op == LeftParenthesis)
            return 0;
        if (is_bino_op(op))
            vt -= 1;
        if (vt < 0)
            return 0;
        opt -= 1;
    }

    return vt == 0 && opt == -1;
}
