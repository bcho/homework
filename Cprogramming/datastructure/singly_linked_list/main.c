#include <stdio.h>
#include "singly_linked_list.h"

#define sep putchar('\n')

void visit(node_t n);

int main()
{
    node_t *link = create("deadbeef");
    traverse(link, visit);
    sep;
    node_t *tmp;
    tmp = pop(&link);
    visit(*tmp);
    sep;
    traverse(link, visit);
    sep;
    push(link, tmp);
    traverse(link, visit);
    sep;
    traverse(search(link, 'b'), visit);
    destory(link);

    return 0;
}

void visit(node_t n)
{
    printf("%c ", n.e);
}
