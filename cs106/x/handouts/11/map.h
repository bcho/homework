#ifndef MAP_H
#define MAP_H

#include "pair.h"

#define T struct map_t
struct map_t;

T *map_create();
void map_free(T *map);
void map_set(struct map_t *map, char *key, char *value);
char *map_get(T *map, char *key);

#undef T
#endif
