#include <stdio.h>

#include "hash.h"

int main()
{
    struct hash_table_t *h;

    h = hash_init(1000);

    hash_insert(h, "hello world!");

    printf("%s\n", hash_retrieve(hash_find(h, "hello world!")));
    printf("%d", hash_find(h, "foo") == NULL);

    hash_free(h);

    return 0;
}
