#include <stdio.h>
#include "singly_link.h"

#define sep printf("\n")

void swap_singly_linked_list();
void print_node(node_t *p);

int main()
{
    printf("singly linked list");
    sep;
    swap_singly_linked_list();
    
    return 0;
}

void print_node(node_t *p)
{
    printf("%c ", retrieve(p));
}

void swap_singly_linked_list()
{
    list_t l = make_list();
    char _[] = "deadbeef", *msg;
    for (msg = _;*msg != '\0';msg++)
        insert(*msg, header(l));
    traversal(print_node, l);
    sep;
    swap(find('a', l), find('a', l)->next, l);
    traversal(print_node, l);
}
