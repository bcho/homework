#include <stdio.h>
#include "deque.h"

#define sep printf("\n")

void print(element_t x);

int main()
{
    char _[] = "deadbeef", *msg;
    queue_t q = create_queue(10);

    for (msg = _;*msg != '\0';msg++)
        inject(*msg, q);
    push('a', q);

    visit(q, print);
    sep;
    eject(q);
    visit_r(q, print);
    sep;
    while (!is_empty(q)) {
        eject(q);
    }
    visit_r(q, print);

    dispose_queue(q);

    return 0;
}

void print(element_t x)
{
    printf("%c ", x);
}
