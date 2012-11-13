#include <stdio.h>
#include "queue.h"

#define sep printf("\n")

int main()
{
    char _[] = "deadbeef";
    char *msg = _;

    queue_t q = create_queue(8);
    printf("%d %d", is_empty(q), is_full(q));
    sep;

    for (;*msg != '\0';msg++) {
        enqueue(*msg, q);
    }

    printf("%d %c", is_full(q), front(q));
    sep;
    dequeue(q);
    printf("%d %c", is_full(q), front(q));
    sep;
    make_empty(q);
    printf("%d %d", is_empty(q), is_full(q));
    dispose_queue(q);

    return 0;
}
