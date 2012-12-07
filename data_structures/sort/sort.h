#ifndef SORT_H
#define SORT_H

typedef long int element_t;
typedef element_t *array;

array create_array(int size);
void dispose_array(array t);
array create_random_array(int size);
void visit_array(array t, int size, void (*visit)(element_t));

void inseretion_sort(array t, int size, int (*cmp)(element_t, element_t));
/* void shell_sort(array t, int size, int (*cmp)(element_t, element_t)); */
void heap_sort(array t, int size, int (*cmp)(element_t, element_t));
void qsort_sort(array t, int size, int (*cmp)(element_t, element_t));

#define MAX_ELEMENTS 2 << 25

#endif
