#include "qsort.h"

#include <stdlib.h>

static int partition(element_t *array, int l, int r,
                     int (*compar)(const void *a, const void *b))
{
    int p;

    p = l;
    for (l += 1;l <= r;) {
        if (compar(&array[p], &array[l]) == -1) {
            swap(&array[l], &array[r]);
            r--;
        } else {
            l++;
        }
    }
    swap(&array[p], &array[r]);
    return r;
}

static void _qsort(element_t *array, int l, int r,
                   int (*compar)(const void *a, const void *b))
{
    int part;

    if (l >= r)
        return;
    part = partition(array, l, r, compar);
    if (part > l)
        _qsort(array, l, part - 1, compar);
    if (part < r)
        _qsort(array, part + 1, r, compar);
}

void quick_sort(element_t *array, int n,
                int (*compar)(const void *a, const void *b))
{
    _qsort(array, 0, n - 1, compar);
}

void quick_sort_std(element_t *array, int n,
                    int (*compar)(const void *a, const void *b))
{
    qsort(array, n, sizeof(element_t), compar);
}
