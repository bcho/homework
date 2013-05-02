#include "select.h"
#include "qsort.h"

#include <stdlib.h>

inline static int median(element_t *_, int a, int b, int c)
{
    return (_[a] > _[b])\
        ? ((_[b] > _[c]) ? b : ((_[a] > _[c]) ? c : a))\
        : ((_[a] > _[c]) ? a : ((_[b] > _[c]) ? c : b));
}

static int partition(element_t *array, int l, int r,
                     int (*compar)(const void *a, const void *b))
{
    int p;

    p = median(array, random() % (r - l + 1), (l + r) >> 1,
               median(array, l, r, random() % (r - l + 1)));
    swap(&array[l], &array[p]);
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

#define MEDIAN 3

static void _qsort_median(element_t *array, int l, int r,
                          int (*compar)(const void *a, const void *b))
{
    int part;

    if (l >= r)
        return;
    if (r - l + 1 < MEDIAN) {
        select_sort(array + l, r - l + 1, compar);
    } else {
        part = partition(array, l, r, compar);
        if (part > l)
            _qsort_median(array, l, part - 1, compar);
        if (part < r)
            _qsort_median(array, part + 1, r, compar);
    }
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
