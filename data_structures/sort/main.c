#include <stdio.h>
#include "sort.h"

#define size 10

#define sep printf("\n")

void print(element_t t);
int cmp(element_t a, element_t b);

int main()
{
    array t = create_random_array(size);
    visit_array(t, size, print);
    sep;
    qsort_sort(t, size, cmp);
    visit_array(t, size, print);
    sep;

    return 0;
}

void print(element_t t)
{
    printf("%ld ", t);
}

/* ascending */
int cmp(element_t a, element_t b)
{
    return (a < b);
}
