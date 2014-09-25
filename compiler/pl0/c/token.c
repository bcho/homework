#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "token.h"


struct token *
token_create(enum token_type type, char *value, int lines, int cols)
{
    struct token *t;

    t = malloc(sizeof(struct token));
    if (t == NULL)
        panic("token_create: unable to allocate memory");

    if (value == NULL)
        t->value = NULL;
    else
        t->value = str_copy(value);

    t->type = type;
    t->pos.lines = lines;
    t->pos.cols = cols;

    return t;
}

void
token_destory(struct token *token)
{
    free(token->value);
    free(token);
}

void
token_print(struct token *token)
{
    printf("Token:\n");
    if (token->value)
        printf("\tvalue: %s\n", token->value);
    printf("\ttype: %d\n", token->type);
    printf("\tlines: %d cols: %d\n", token->pos.lines, token->pos.cols);
}
