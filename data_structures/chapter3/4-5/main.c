#include <stdio.h>
#include "link.h"

#define sep printf("\n")
#define BASE ('a' - 1)

list_t list_intersection(list_t a, list_t b);
list_t list_union(list_t a, list_t b);

list_t make_ascending_list(int upperlimit);
void print_node(node_t *n);

int main()
{
    list_t a = make_ascending_list(5);
    insert('z', header(a));
    list_t b = make_ascending_list(12);
    traversal(print_node, a);
    sep;
    traversal(print_node, b);
    sep;
    list_t u = list_union(a, b);
    traversal(print_node, u);
    sep;
    list_t i = list_intersection(a, b);
    traversal(print_node, i);
    
    destory(a);
    destory(b);
    destory(u);
    destory(i);

    return 0;
}

list_t list_intersection(list_t a, list_t b)
{
    list_t l = make_list();
    pos_t cur;
    for (cur = header(a)->next;cur;cur = cur->next) {
        if (find(retrieve(cur), b) && !find(retrieve(cur), l))
            insert(retrieve(cur), header(l));
    }
    return l;
}

list_t list_union(list_t a, list_t b)
{
    list_t l = make_list();
    pos_t cur_a, cur_b;
    for (cur_a = header(a)->next, cur_b = header(b)->next;cur_a || cur_b;) {
        if (cur_a && !find(retrieve(cur_a), l))
            insert(retrieve(cur_a), header(l));
        if (cur_a)
            cur_a = cur_a->next;
        if (!find(retrieve(cur_b), l))
            insert(retrieve(cur_b), header(l));
        if (cur_b)
            cur_b = cur_b->next;
    }
    return l;
}

list_t make_ascending_list(int upperlimit)
{
    list_t l = make_list();
    int i;
    for (i = upperlimit;i > 0;i--)
        insert(BASE + i, header(l));
    return l;
}

void print_node(node_t *n)
{
    printf("%c ", retrieve(n));
}
