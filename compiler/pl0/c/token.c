#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "token.h"


struct reserved_value {
    enum token_type type;
    char *value;
};

static struct reserved_value RESERVED_VALUES[] = {
    { CONST     ,  "const" },
    { VAR       ,  "var" },
    { PROCEDURE ,  "procedure"},
    { BEGIN     ,  "begin"},
    { END       ,  "end"},
    { IF        ,  "if"},
    { THEN      ,  "then"},
    { WHILE     ,  "while"},
    { DO        ,  "do"},
    { ODD       ,  "odd"},
    { CALL      ,  "call"}
};


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

struct token *
token_create_from_ident(char * value, int lines, int cols)
{
    int i;
    struct reserved_value keyword;

    /* check if it is a keyword */
    for (i = 0; i < NELEMS(RESERVED_VALUES); i++) {
        keyword = RESERVED_VALUES[i];
        /* we just simply ignore case here :) */
        if (strncasecmp(keyword.value, value, strlen(value)) == 0)
            return token_create(keyword.type, keyword.value, lines, cols);
    }

    /* it can be an indent */
    return token_create(IDENT, value, lines, cols);
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
