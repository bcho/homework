#ifndef POSTFIX_H
#define POSTFIX_H

#include "stack.h"

element_t evaluate(char *formula);
int is_digit(char c);
int is_op(char c);

#define MAX_OP 1000
#endif
