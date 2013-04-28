#ifndef HEAP_H
#define HEAP_H

#include "sort.h"

void heap_sort(element_t *array, int n, int (*cmpar)(void *a, void *b));

#endif
