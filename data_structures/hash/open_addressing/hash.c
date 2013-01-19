#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash.h"
#include "../package.h"

#define T struct node_t
#define HT struct hash_table_t
#define ST enum node_status_t

#define max(a, b) (((a) > (b) ) ? (a) : (b))
#define INIT_SIZE 13

static unsigned int hash(char *hint, HT *table)
{
    unsigned int h;

    for (h = 0;*hint != '\0';hint++)
        h = (h << 5) + *hint;

    return h % table->size;
}

HT *hash_init(int size)
{
    HT *table;
    int i;

    table = malloc(sizeof(HT));
    assert(table != NULL);
    table->size = max(INIT_SIZE, size);
    table->nodes = malloc(table->size * sizeof(T));

    assert(table->nodes != NULL);
    for (i = 0;i < table->size;i++)
        table->nodes[i].status = EMPTY;
    table->used = 0;

    return table;
}

void hash_free(HT *table)
{
    assert(table != NULL);
    assert(table->nodes != NULL);
    free(table->nodes);
    free(table);
}

HT *hash_rehash(HT *table)
{
    HT *new;
    int i;

    assert(table != NULL);
    new = hash_init(table->size * 2);
    for (i = 0;i < table->size;i++)
        if (table->nodes[i].status == FULL)
            hash_insert(new, table->nodes[i].value);
    hash_free(table);
    return new;
}

T *hash_find(HT *table, char *key)
{
    unsigned int current;
    int collision;

    current = hash(key, table);
    collision = 0;
    while (table->nodes[current].status != EMPTY &&
           strcmp(table->nodes[current].value->key, key) != 0) {
        /* ? */
        current += 2 * ++collision - 1;
        if (current >= table->size)
            current -= table->size;
    }
    return table->nodes + current;
}

void hash_insert(HT *table, struct package_t *package)
{
    T *pos;

    pos = hash_find(table, package->key);
    if (pos->status == EMPTY) {
        pos->status = FULL;
        pos->value = package;
        if (++table->used >= table->size / 2)
            table = hash_rehash(table);
    }
}

struct package_t *hash_delete(HT *table, char *key)
{
    T *node;
    struct package_t *p;

    if ((node = hash_find(table, key)) == NULL) {
        return NULL;
    } else {
        node->status = EMPTY;
        p = node->value;
        node->value = NULL;
        return p;
    }

    return NULL;
}

struct package_t *hash_retrieve(T *node)
{
    return node->value;
}
