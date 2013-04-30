#ifndef MERGE_H
#define MERGE_H

#include "sort.h"

void merge_sort(element_t *array, int n,
                int (*compar)(const void *a, const void *b));

#endif
