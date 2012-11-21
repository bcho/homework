#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef enum {
    OPERATOR,
    OPERAND
} TOKEN_TYPE;
typedef enum {
    PAIR = 1,
    PLUS = 1 << 1, SUBTRACT = 1 << 1,
    MULTLY = 1 << 2, DIV = 1 << 2
} OPERATOR_PRECENDENCE;
#define SUPPORTEDOPERATOR "+-*/()"

struct token_r {
    TOKEN_TYPE type;
    int value;
};
typedef struct token_r *token_t;

token_t new_token(TOKEN_TYPE type, int value);
void dispose_token(token_t t);

int parse_formula(char src[], token_t dest[]);
int evaluate(token_t formula[], int length);

OPERATOR_PRECENDENCE op_precendence(char op);

/* your formula should not longer than that */
#define MAX_OP 1000
#endif
