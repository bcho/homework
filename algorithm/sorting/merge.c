#include <stdlib.h>

#include "merge.h"

static void ncopy(element_t *dest, const element_t *src, int n)
{
    int i;

    for (i = 0;i < n;i++)
        dest[i] = src[i];
}

static void merge(element_t *array, int l, int r, int m,
                  int (*compar)(const void *a, const void *b))
{
    int i, j;
    element_t *left, *right;

    left = malloc(sizeof(element_t) * (m - l + 1));
    right = malloc(sizeof(element_t) * (r - (m + 1) + 1));
    ncopy(left, array + l, m - l + 1);
    ncopy(right, array + m + 1, r - (m + 1) + 1);

    for (i = 0, j = 0;i < (m - l + 1) && j < (r - (m + 1) + 1);)
        if (compar(&left[i], &right[j]) == -1) {
            array[i + j + l] = left[i];
            i++;
        } else {
            array[i + j + l] = right[j];
            j++;
        }
    for (;i < m - l + 1;i++)
        array[i + j + l] = left[i];
    for (;j < r - (m + 1) + 1;j++)
        array[i + j + l] = right[j];

    free(left);
    free(right);
}

static void sort(element_t *array, int l, int r,
                 int (*compar)(const void *a, const void *b))
{
    int m;

    if (l >= r)
        return;
    m = (l + r) / 2;
    sort(array, l, m, compar);
    sort(array, m + 1, r, compar);
    merge(array, l, r, m, compar);
}

void merge_sort(element_t *array, int n,
                int (*compar)(const void *a, const void *b))
{
    sort(array, 0, n - 1, compar);
}
