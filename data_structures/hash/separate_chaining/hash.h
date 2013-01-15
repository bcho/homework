#ifndef HASH_H
#define HASH_H

typedef char value_t;

struct list_node_t;
struct hash_table_t;

struct hash_table_t *hash_init(int size);
void hash_free(struct hash_table_t *table);
struct list_node_t *hash_find(struct hash_table_t *table, value_t *key);
void hash_insert(struct hash_table_t *table, value_t *key);
value_t *hash_retrieve(struct list_node_t *node);

#endif
