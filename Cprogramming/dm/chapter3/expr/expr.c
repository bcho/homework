#include "expr.h"

/* op */
#define PLUS '+'
#define MULT '*'
#define NOT '~'
#define LEFTP '('
#define RIGHP ')'

#define STACK_SIZE 200


static int op_level(char op)
{
    if (op == PLUS)
        return 0;
    if (op == MULT)
        return 1;
    if (op == NOT)
        return 2;
    if (op == LEFTP || op == RIGHP)
        return 3;
    return -1;
}

static int is_op(char x)
{
    return (x == PLUS || x == MULT || x == NOT || x == LEFTP || x == RIGHP);
}

static int is_whitespace(char x)
{
    return x == ' ';
}

static int is_value(char x)
{
    return (x >= 'A' && x <= 'Z');
}

int validate_expr(char *expression)
{
    char x, op;
    int vt, opt, level;
    char ops[STACK_SIZE];

    vt = -1; opt = -1;
    while ((x = *expression++) != '\0')
        if (is_value(x)) {
            vt += 1;
        } else if (is_op(x)) {
            level = op_level(x);
            while (opt >= 0 && level < op_level(ops[opt]) && \
                    ops[opt] != LEFTP) {
                op = ops[opt];
                opt -= 1;
                if (op == PLUS || op == MULT)
                    vt -= 1;
                if (vt < 0)
                    return 0;
            }
            if (x == RIGHP) {
                while (opt >=0 && ops[opt] != LEFTP) {
                    op = ops[opt];
                    if (op == PLUS || op == MULT)
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
        if (op == LEFTP)
            return 0;
        if (op == PLUS || op == MULT)
            vt -= 1;
        if (vt < 0)
            return 0;
        opt -= 1;
    }

    return vt == 0 && opt == -1;
}
