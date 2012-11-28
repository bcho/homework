#include <stdio.h>
#include <string.h>
#include "heap.h"

#define sep printf("\n")

int main()
{
    char msg[] = "deadbeef";
    int i;
    heap_t h = create_heap(20);

    for (i = 0;i < strlen(msg);i++)
        h->array[++h->size] = msg[i];
    build_heap(h);

    for (;!is_empty(h);)
        printf("%c ", pop_min(h));
    sep;

    return 0;
}
