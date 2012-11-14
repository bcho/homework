#include <stdio.h>
#include "doubly_linked_list.h"

#define sep printf("\n")

void print_node(node_t *p);

int main()
{
    char _[] = "deadbeef", *msg;
    list_t *l = make_list();
    for (msg = _;*msg != '\0';msg++)
        insert(*msg, *l, header(*l));
    traversal(print_node, first(*l), 0);
    sep;
    swap(find('a', *l), find('a', *l)->next, *l);
    traversal(print_node, first(*l), 0);

    return 0;
}

void print_node(node_t *p)
{
    printf("%c ", retrieve(p));
}
