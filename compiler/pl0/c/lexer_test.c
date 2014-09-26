#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "token.h"
#include "lexer.h"

static char *good_samples[] = {
    "examples/simple.pl0",
    "examples/helloworld.pl0",
    "examples/nested_procedures.pl0",
    "examples/not_simple.pl0"
};

void
test_good_samples()
{
    int i;
    FILE *src;
    struct token *t;

    for (i = 0; i < NELEMS(good_samples); i++) {
        printf("checking %s:\n", good_samples[i]);
        src = fopen(good_samples[i], "r");
        lexer_set_src_stream(src);

        while (1) {
            t = token_get();
            if (t->type == END_OF_FILE)
                break;

            token_print(t);
            assert(t->type != ERROR);
            token_destory(t);
        }
        token_destory(t);

        fclose(src);
    }
}

int
main()
{
    test_good_samples();

    return 0;
}
