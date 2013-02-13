#include <stdlib.h>
#include <assert.h>

#include "pair.h"

#define T struct pair_t

T *pair_create(char *key, char *value)
{
    T *new;

    new = malloc(sizeof(*new));
    assert(new != NULL);
    new->key = key;
    new->value = value;
    return new;
}

char *pair_key(T *pair)
{
    assert(pair != NULL);
    return pair->key;
}

char *pair_value(T *pair)
{
    assert(pair != NULL);
    return pair->value;
}

void pair_free(T *pair)
{
    assert(pair != NULL);
    free(pair);
}
