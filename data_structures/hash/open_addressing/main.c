#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../package.h"
#include "hash.h"

int main()
{
    struct hash_table_t *h;
    struct package_t *p;

    p = package_create("greeting", "hello world!");

    h = hash_init(1000);

    hash_insert(h, p);

    printf("%s\n", hash_retrieve(hash_find(h, p->key))->value);
    printf("%d ", hash_find(h, "foo")->status != EMPTY);

    hash_delete(h, p->key);
    printf("%d", hash_find(h, p->key)->status != EMPTY);

    package_free(p);
    hash_free(h);

    return 0;
}
