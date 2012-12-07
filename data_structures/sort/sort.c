#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "sort.h"

/* it's dangerous if the outest pair it miss */
#define min(a, b) (((a) < (b)) ? (a) : (b))

array create_array(int size)
{
    array buf = malloc(sizeof(element_t) * min(size, MAX_ELEMENTS));
    assert(buf != NULL);
    return buf;
}

void dispose_array(array t)
{
    assert(t != NULL);
    free(t);
}

array create_random_array(int size)
{
    int i;
    array buf = create_array(size);

    srand(time(NULL));
    for (i = 0;i < min(size, MAX_ELEMENTS);i++)
        *(buf + i) = rand();

    return buf;
}

void visit_array(array t, int size, void (*visit)(element_t))
{
    int i;
    for (i = 0;i < size;i++)
        visit(*(t + i));
}

static void swap(element_t *a, element_t *b)
{
    element_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void inseretion_sort(array t, int size, int (*cmp)(element_t, element_t))
{
    int i, j;
    element_t cur;

    for (i = 1;i < size;i++) {
        /* assume that from 0 to i - 1 is already sorted,
         * we now find a suit position for t[i] in the
         * sorted part by shifting the previous elements.
         */
        for (cur = t[i], j = i;j > 0 && cmp(cur, t[j - 1]);j--)
                t[j] = t[j - 1];
        t[j] = cur;
    }
}

void heap_sink(int start, array t, int size, int (*cmp)(element_t, element_t))
{
    int i, child;
    for (i = start;i * 2 + 1 < size;i=child) {
        /* root locations at 0 */
        child = i * 2 + 1;
        if (child < size - 1 && cmp(t[child], t[child + 1]))
            child++;
        if (cmp(t[i], t[child]))
            swap(&t[i], &t[child]);
        else
            break;
    }
}

void heap_sort(array t, int size, int (*cmp)(element_t, element_t))
{
    int i, heap_size;

    /* build heap */
    for (i = size / 2;i >= 0;i--)
        heap_sink(i, t, size, cmp);

    /* sort */
    for (i = 0, heap_size = size;i < size;i++) {
        swap(&t[0], &t[--heap_size]);
        heap_sink(0, t, heap_size, cmp);
    }
}

int qsort_pivot(int left, int right)
{
    return (left + right) >> 1;
}

void _qsort(int left, int right, array t, int (*cmp)(element_t, element_t))
{
    int last, i;

    if (left >= right)
        return;

    swap(&t[qsort_pivot(left, right)], &t[left]);
    for (last = left, i = left + 1;i <= right;i++)
        if (cmp(t[i], t[left]))
            swap(&t[i], &t[++last]);
    swap(&t[left], &t[last]);

    _qsort(left, last - 1, t, cmp);
    _qsort(last + 1, right, t, cmp);
}

void qsort_sort(array t, int size, int (*cmp)(element_t, element_t))
{
    _qsort(0, size - 1, t, cmp);
}
