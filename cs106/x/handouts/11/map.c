#include <stdlib.h>
#include <assert.h>

#include "str.h"
#include "pair.h"
#include "map.h"

#define INIT_SIZE 421

enum status_t {
    EMPTY,
    FULL
};

struct map_t {
    int size, used;
    struct pair_t **items;
    enum status_t *status;
};
#define T struct map_t

static unsigned int hash(char *hint, T *map)
{
    unsigned int h;

    for (h = 0;*hint != '\0';hint++)
        h = (h << 5) + *hint;

    return h % map->size;
}

T *map_create()
{
    T *new;
    int i;

    new = malloc(sizeof(T));
    assert(new != NULL);
    new->size = INIT_SIZE;
    new->items = malloc(sizeof(struct pair_t) * new->size);
    assert(new->items != NULL);
    new->status = malloc(sizeof(enum status_t) * new->size);
    assert(new->status != NULL);

    for (i = 0;i < new->size;i++)
        new->status[i] = EMPTY;
    new->used = 0;

    return new;
}

void map_free(T *map)
{
    int i;

    assert(map != NULL && map->items != NULL && map->status != NULL);
    free(map->status);
    for (i = 0;i < map->size;i++)
        pair_free(map->items[i]);
    free(map->items);
    free(map);
}

int map_find(T *map, char *key)
{
    unsigned int current;
    int collision;

    current = hash(key, map);
    collision = 0;
    while (map->status[current] != EMPTY && \
            str_cmp(pair_key(map->items[current]), key) != 0) {
        current += 2 * collision - 1;
        if (current >= map->size)
            current -= map->size;
    }
    return current;
}

T *map_rehash(T *map)
{
    T *new;
    int i;

    assert(map != NULL);
    new = map_create(2 * map->size);
    for (i = 0;i < map->size;i++)
        if (map->status[i] == FULL)
            map_set(new, pair_key(map->items[i]), pair_value(map->items[i]));
    map_free(map);
    return new;
}

void map_set(T *map, char *key, char *value)
{
    int pos;

    pos = map_find(map, key);
    if (map->status[pos] == EMPTY) {
        map->status[pos] = FULL;
        map->items[pos] = pair_create(key, value);
        if (++map->used >= map->size / 2)
            map = map_rehash(map);
    }
}

char *map_get(T *map, char *key)
{
    int pos;

    pos = map_find(map, key);
    if (map->status[pos] != EMPTY)
        return pair_value(map->items[pos]);
    return NULL;
}
