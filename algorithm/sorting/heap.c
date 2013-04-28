#include "heap.h"

static int parent(int cur, int size)
{
    if (cur == 0)
        return -1;
    return (cur - 1) / 2;
}

static int lchild(int cur, int size)
{
    if (2 * cur + 1 >= size)
        return -1;
    return 2 * cur + 1;
}

static int rchild(int cur, int size)
{
    if (2 * cur + 2 >= size)
        return -1;
    return lchild(cur, size) + 1;
}

static void bubble_down(element_t *array, int cur, int size,
                        int (*compar)(void *a, void *b))
{
    int child;

    child = lchild(cur, size);
    if (child == -1)
        return;
    if (child + 1 < size && compar(&array[child], &array[child + 1]) == -1)
        child += 1;
    if (compar(&array[cur], &array[child]) == -1) {
        swap(&array[cur], &array[child]);
        bubble_down(array, child, size, compar);
    }
}

static void build_heap(element_t *array, int n, int (*compar)(void *a, void *b))
{
    int i;

    for (i = n / 2;i >= 0;i--)
        bubble_down(array, i, n, compar);
}

void heap_sort(element_t *array, int n, int (*compar)(void *a, void *b))
{
    int i;
    int size;

    build_heap(array, n, compar);
    for (i = 0, size = n;i < n;i++) {
        swap(&array[0], &array[size - 1]);
        size--;
        bubble_down(array, 0, size, compar);
    }
}
