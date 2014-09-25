#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "token.h"
    
int
main(int argc, char *argv[])
{
    struct token *t;

    t = token_create(IDENT, "foobar", 0, 0);

    assert(t->type == IDENT);
    token_print(t);

    token_destory(t);

    return 0;
}
