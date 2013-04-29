#include "select.h"

void select_sort(element_t *array, int n,
                 int (*compar)(const void *a, const void *b))
{
    int i, j, select;

    for (i = 0;i < n;i++) {
        for (select = i, j = i;j < n;j++)
            if (compar(&array[select], &array[j]) == 1)
                select = j;
        swap(&array[select], &array[i]);
    }
}
