#ifndef PAIR_H
#define PAIR_H

#define T struct pair_t
struct pair_t {
    char *key, *value;
};

T *pair_create(char *key, char *value);
char *pair_key(T *pair);
char *pair_value(T *pair);
void pair_free(T *pair);

#undef T
#endif
