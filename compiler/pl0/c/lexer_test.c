#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "token.h"
#include "lexer.h"

int
main()
{
    struct token *t;

    lexer_set_src_stream(stdin);
    while (1) {
        t = token_get();
        printf("type: %d\n", t->type);
        if (t->type == END_OF_FILE)
            break;
        token_destory(t);
    }
    token_destory(t);

    return 0;
}
