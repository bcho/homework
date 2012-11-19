#include <stdio.h>
#include "double_stack.h"

#define sep printf("\n")

int main()
{
    char _[] = "deadbeef", *msg;

    double_stack_t s = create_stack(8);

    printf("%d %d %d", is_empty(s), is_empty_a(s), is_empty_b(s));
    sep;

    for (msg = _;*msg != 'b';msg++)
        push_a(*msg, s);
    for (;*msg != '\0';msg++)
        push_b(*msg, s);

    printf("%d %d %d %d", is_empty(s), is_empty_a(s), is_empty_b(s), \
                          is_full(s));
    sep;

    printf("%d->%c %d->%c", s->atop, top_a(s), s->btop, top_b(s));
    sep;
    
    push_a('x', s);
    printf("%d->%c %d->%c", s->atop, top_a(s), s->btop, top_b(s));
    sep;

    pop_a(s);
    pop_b(s);
    printf("%d->%c %d->%c", s->atop, top_a(s), s->btop, top_b(s));

    dispose_stack(s);

    return 0;
}
