#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "package.h"

#define T struct package_t

T *package_create(const char *key, const char *value)
{
    T *package;

    package = malloc(sizeof(T));
    assert(package != NULL);
    package_set_value(package, value);
    package_set_key(package, key);

    return package;
}

static void string_cpy(char **dest, const char *src)
{
    *dest = malloc(sizeof(char) * strlen(src));
    assert(*dest != NULL);
    strcpy(*dest, src);
}

void package_set_value(T *package, const char *value)
{
    assert(package != NULL);
    string_cpy(&package->value, value);
}

void package_set_key(T *package, const char *key)
{
    assert(package != NULL);
    string_cpy(&package->key, key);
}

char *package_get_value(T *package)
{
    assert(package != NULL);
    return package->value;
}

char *package_get_key(T *package)
{
    assert(package != NULL);
    return package->key;
}

void package_free(T *package)
{
    assert(package != NULL);
    free(package->key);
    free(package->value);
    free(package);
}
