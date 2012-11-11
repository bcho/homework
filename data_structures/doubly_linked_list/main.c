#include <stdio.h>
#include "link.h"

#define sep printf("\n")

void print_node(node_t *p);

int main()
{
    list_t l = *make_list();
    printf("%d %d %d", is_empty(l), is_last(l.head, l), is_last(l.tail, l));
    sep;

    char _[] = "deadbeef";
    char *msg = _;
    for (;*msg != '\0';msg++) {
        insert(*msg, l, header(l));
    }
    traversal(print_node, first(l), 0);
    sep;
    traversal(print_node, find('a', l), 0);
    sep;
    insert('v', l, find('a', l));
    traversal(print_node, l.tail, 1);
    sep;
    traversal(print_node, first(l), 0);
    sep;
    printf("%c", retrieve(pop('e', l)));
    sep;
    traversal(print_node, first(l), 0);
    sep;
    destory(l);
    printf("%d", is_empty(l));

    return 0;
}

void print_node(node_t *p)
{
    printf("%c ", p->e);
}
