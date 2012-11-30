#include <stdio.h>
#include "heap.h"

#define COUNT 15

const int num[COUNT] = {10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2};

void print_heap(heap_t q);

int main()
{
    int i;

    heap_t a, b;

    a = create_heap(COUNT);
    b = create_heap(COUNT);

    for (i = 0;i < COUNT;i++) {
        insert(num[i], a);
        b->array[++b->size] = num[i];
    }
    build_heap(b);

    print_heap(a);
    print_heap(b);

    for (;!is_empty(a);)
        printf("%d ", pop_min(a));

    return 0;
}

void print_heap(heap_t q)
{
    int i;
    for (i = 1;i <= q->size;i++)
        printf("%d ", q->array[i]);
    printf("\n");
}
