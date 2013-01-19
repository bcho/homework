#ifndef HASH_H
#define HASH_H

#include "../package.h"

#define T struct node_t
#define HT struct hash_table_t
#define ST enum node_status_t

enum node_status_t {
    EMPTY,
    FULL
};
struct node_t {
    struct package_t *value;
    ST status;
};
struct hash_table_t {
    int size, used;
    struct node_t *nodes;
};

HT *hash_init(int size);
void hash_free(HT *table);
HT *hash_rehash(HT *table);
T *hash_find(HT *table, char *key);
void hash_insert(HT *table, struct package_t *package);
struct package_t *hash_delete(HT *table, char *key);
struct package_t *hash_retrieve(T *node);

#undef T
#undef HT
#endif
