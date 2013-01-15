#ifndef HASH_H
#define HASH_H

#include "../package.h"

struct list_node_t;
struct hash_table_t;

struct hash_table_t *hash_init(int size);
void hash_free(struct hash_table_t *table);
struct list_node_t *hash_find(struct hash_table_t *table, char *key);
void hash_insert(struct hash_table_t *table, char *key,
                 struct package_t *package);
struct list_node_t *hash_delete(struct hash_table_t *table, char *key);
struct package_t *hash_retrieve(struct list_node_t *node);

#endif
