// Consider a left recursion grammar:
//
// exp = exp + num | num
// num = 0|1|2|3|4|5|6|7|8|9
//
// We can remove left recursion by employing exp':
//
// exp  = num exp'
// exp' = + num exp' | eps
//
// Here is the top-down parser:

typedef int  token_type;

#define PLUS 0
#define NUMBER 1

int match(token_type type);         /* Match a token with specify type. */
token_type peek();                  /* Peek a token. */

void parse_exp();
void parse_exp_minus();

void
parse_exp()
{
    match(NUMBER);
    parse_exp_minus();
}

void
parse_exp_minus()
{
    if (peek() == PLUS)
        parse_exp();
    else                            /* eps */
        return;
}

// But the problem is, this is will change the op '+' 's assocication,
// which became right-associate in exp'.
//
// For example, expression likes:
//
//  5 - 3 + 2
//
// Parser above will create:
//
//      -
//     / \
//    5   + 
//       / \
//      3   2
//
// But what we expect is:
//
//      +
//     / \
//    -   2
//   / \
//  5   3
//
// 
// In order to fix the association change, we can:
//
// 1) use EBNF to rewrite to BNF grammar:
//
//      exp = num [ + exp ]                 ; expressions inside the bracket
//                                          ; mean can repeat zero or more times
// 
// 
// 2) pass value to the exp' node:

int parse_exp_left();
int parse_exp_minus_left(int);

int
parse_exp_left()
{
    return parse_exp_minus_left(match(NUMBER));
}

int
parse_exp_minus_left(int value_calculated)
{
    if (peek() == PLUS) {
        match(PLUS);
        value_calculated += match(NUMBER);

        return parse_exp_minus_left(value_calculated);
    } else {                                            /* eps */
        return value_calculated;
    }
}

// By doing so, we can convert the syntax tree to expected one.
