#ifndef CONVERT_H
#define CONVERT_H

#include "calculator.h"
#include "tree.h"

int infix2postfix(token_t src[], token_t dest[], int length);
/* build an expressions tree */
void postfix2tree(token_t src[], tree_t *dest, int length);
#endif
