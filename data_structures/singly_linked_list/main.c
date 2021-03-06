#include <stdio.h>
#include "link.h"

#define sep printf("\n")

void print_node(node_t *p);

int main()
{
    list_t l = make_list();

    char _[] = "deadbeef";
    char *msg = _;
    for (;*msg != '\0';msg++) {
        insert(*msg, header(l));
    }
    traversal(print_node, l);
    sep;
    printf("%c", find('a', l)->e);
    sep;
    insert('v', find('a', l));
    traversal(print_node, l);
    sep;
    traversal(print_node, pop('e', l));
    sep;
    destory(l);
    printf("%d %d", is_empty(l), is_last(header(l)));
    sep;

    return 0;
}

void print_node(node_t *p)
{
    printf("%c ", p->e);
}
