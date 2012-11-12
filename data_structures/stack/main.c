#include <stdio.h>
#include "stack.h"

#define sep printf("\n")

int main()
{
    stack_t s = create_stack(8);
    char _[] = "deadbeef";
    char *msg = _;

    printf("%d %d", is_empty(s), is_full(s));
    sep;
    for (;*msg != '\0';msg++) {
        push(*msg, s);
    }
    printf("%c", top(s));
    sep;
    printf("%d %d", is_empty(s), is_full(s));
    sep;
    pop(s);
    printf("%c", top(s));
    sep;
    make_empty(s);
    printf("%d %d", is_empty(s), is_full(s));
    dispose_stack(s);

    return 0;
}
