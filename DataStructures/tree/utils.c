#include "utils.h"

#include <stdlib.h>


char *Malloc(size_t size)
{
    char *buffer;

    if ((buffer = malloc(size)) == NULL)
        exit(-1);
    return buffer;
}

char *Realloc(char *ptr, size_t size)
{
    return realloc(ptr, size);
}

void Assert(int cond)
{
    if (!cond)
        exit(-1);
}
