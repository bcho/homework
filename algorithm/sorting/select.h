#ifndef SELECT_H
#define SELECT_H

#include "sort.h"

void select_sort(element_t *array, int n,
                 int (*compar)(const void *a, const void *b));

#endif
