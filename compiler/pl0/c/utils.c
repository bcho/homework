#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"


void
panic(char *message)
{
    fprintf(stderr, "error occoured: %s\n", message);
    exit(-1);
}


char *
str_copy(char *src)
{
    size_t len;
    char *dest;

    len = strlen(src);
    dest = malloc((len + 1) * sizeof(char));
    if (dest == NULL)
        panic("str_copy: unable to allocate memory");

    strncpy(dest, src, len);
    dest[len] = 0;

    return dest;
}
