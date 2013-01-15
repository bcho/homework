#ifndef PACKAGE_H
#define PACKAGE_H

struct package_t {
    char *key;
    char *value;
};
#define T struct package_t

T *package_create(const char *key, const char *value);
void package_free(T *package);
void package_set_value(T *package, const char *value);
void package_set_key(T *package, const char *key);
char *package_get_value(T *package);
char *package_get_key(T *package);

#undef T
#endif
