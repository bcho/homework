#include <stdio.h>
#include "link.h"

#define sep printf("\n")

void print_lots(list_t l, list_t p);
list_t create_ascending_list(int limit);
void print_node(node_t *e);

int main()
{
    list_t l = create_ascending_list(6);
    list_t p = create_ascending_list(5);
    
    traversal(print_node, l);
    sep;
    traversal(print_node, p);
    sep;

    print_lots(l, p);
    sep;
    return 0;
}

void print_node(node_t *e)
{
    printf("%d ", e->e);
}

void print_lots(list_t l, list_t p)
{
    int i;
    pos_t a, b;
    for (i = 1, a = header(l)->next, b = header(p)->next; a && b;
         a = a->next, i++) {
        if (retrieve(b) == i) {
            printf("(%d, %d) ", i, retrieve(a));
            b = b->next;
        }
    }
}

list_t create_ascending_list(int limit)
{
    int i;
    list_t l = make_list();
    for (i = limit;i > 0;i--)
        insert(i, header(l));
    return l;
}
