#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

char *Malloc(size_t size);
char *Realloc(char *ptr, size_t size);
void Assert(int cond);

#endif
