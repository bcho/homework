#ifndef QSORT_H
#define QSORT_H

#include "sort.h"

void quick_sort(element_t *array, int n,
                int (*compar)(const void *a, const void *b));
void quick_sort_std(element_t *array, int n,
                    int (*compar)(const void *a, const void *b));
#endif
