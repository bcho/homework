#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hash.h"

#define MINSIZE 13
#define MAXSIZE 68023

struct list_node_t {
    value_t *value;
    struct list_node_t *next;
};

struct hash_table_t {
    int size;
    struct list_node_t **nodes;
};

static int find_prime(int hint)
{
    int i;
    static int primes[] = { 509, 1051, 2111, 2111, 4229,
                            8461, 16993, 33997, MAXSIZE };

    if (hint < MINSIZE || hint > MAXSIZE)
        return 0;

    for (i = 0;primes[i] < hint;i++)
        ;
    return primes[i];
}

static unsigned int hash(value_t *key, struct hash_table_t *table)
{
    unsigned int ret;

    for (ret = 0;*key != '\0';key++)
        ret += (ret << 5) + *key;

    return ret % table->size;
}

struct hash_table_t *hash_init(int size)
{
    struct hash_table_t *table;
    int i;

    table = malloc(sizeof *table);
    assert(table != NULL);

    table->size = find_prime(size);
    assert(table-size > 0);
    table->nodes = malloc(sizeof(struct list_node_t) * table->size);
    assert(table->nodes != NULL);
    for (i = 0;i < table->size;i++)
        table->nodes[i] = NULL;

    return table;
}

void hash_free(struct hash_table_t *table)
{
    assert(table != NULL && table->nodes != NULL);
    free(table->nodes);
    free(table);
}

struct list_node_t *hash_find(struct hash_table_t *table, value_t *key)
{
    struct list_node_t *i;

    for (i = table->nodes[hash(key, table)]; \
         (i != NULL) && (strcmp(key, hash_retrieve(i)) != 0);
         i = i->next)
        ;

    return i;
}

void hash_insert(struct hash_table_t *table, value_t *key)
{
    struct list_node_t *pos, *new;
    int key_hash;

    pos = hash_find(table, key);
    if (pos == NULL) {
        new = malloc(sizeof(struct list_node_t));
        assert(new);
        key_hash = hash(key, table);
        pos = table->nodes[key_hash];
        table->nodes[key_hash] = new;
        new->next = pos;
        new->value = malloc(strlen(key) * sizeof(value_t));
        assert(new->value != NULL);
        strcpy(new->value, key);
    }
}

value_t *hash_retrieve(struct list_node_t *node)
{
    assert(node != NULL);
    return node->value;
}
