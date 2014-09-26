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
test_from_stream(FILE *src)
{
    struct token *t;

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
}

void
test_good_samples()
{
    int i;
    FILE *src;
    struct token *t;

    for (i = 0; i < NELEMS(good_samples); i++) {
        printf("checking %s:\n", good_samples[i]);

        src = fopen(good_samples[i], "r");
        test_from_stream(src);
        fclose(src);
    }
}

int
main(int argc, char *argv[])
{
    test_good_samples();

    if (argc >= 2 && strcmp(argv[1], "stdin") == 0)
        test_from_stream(stdin);

    return 0;
}
