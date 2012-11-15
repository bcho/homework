#include <stdio.h>
#include "link.h"

void reverse(list_t l);
void print_node(node_t *n);

int main()
{
    char _[] = "db", *msg;
    list_t l = make_list();
    for (msg = _;*msg != '\0';msg++)
        insert(*msg, header(l));
    traversal(print_node, l);
    printf("\n");
    reverse(l);
    traversal(print_node, l);
    destory(l);
    return 0;
}

void print_node(node_t *n)
{
    printf("%c ", n->e);
}

void reverse(list_t l)
{
    if (is_empty(l))
        return;
    node_t *tmp, *i, *r;

    r = NULL;
    for (i = l->next;i;) {
        tmp = i->next;
        i->next = r;
        r = i;
        i = tmp;
    }
    l->next = r;
}
