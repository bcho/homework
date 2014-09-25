#include <assert.h>
#include <string.h>

#include "token.h"

int
main()
{
    struct token *t;

    /* token without value */
    t = token_create(END_OF_FILE, 0, 0, 0);
    assert(t->type == END_OF_FILE);
    assert(t->value == 0);
    assert(t->pos.lines == 0);
    assert(t->pos.cols == 0);
    token_destory(t);
    
    /* token with value */
    t = token_create(IDENT, "foobar", 0, 0);
    assert(t->type == IDENT);
    assert(strcmp(t->value, "foobar") == 0);
    assert(t->pos.lines == 0);
    assert(t->pos.cols == 0);

    token_print(t);
    token_destory(t);
    
    return 0;
}
