#include <stdio.h>
#include <stdlib.h>
#include "link.h"

node_t *new_node(void)
{
    node_t *p = malloc(sizeof(struct node));
    if (p == NULL)
        printf("Out of memory!");
    return p;
}

void free_node(node_t *node)
{
    free(node);
}

list_t make_list(void)
{
    node_t *header = new_node();
    header->next = NULL;
    return header;
}

int is_empty(list_t l)
{
    return (l->next == NULL);
}

int is_last(pos_t p, list_t l)
{
    return p->next == NULL;
}

pos_t find(element_t x, list_t l)
{
    for (;l && l->e != x;l = l->next)
        ;
    return l;
}

node_t *pop(element_t x, list_t l)
{
    pos_t previous;
    node_t *tmp;

    previous = find_previous(x, l);

    if (!is_last(previous, l)) {
        tmp = previous->next;
        previous->next = tmp->next;
        return tmp;
    }

    return NULL;
}

pos_t find_previous(element_t x, list_t l)
{
    for (;l && l->next->e != x;l = l->next)
        ;
    return l;
}

void insert(element_t x, list_t l, pos_t p)
{
    node_t *tmp = new_node();
    tmp->e = x;
    tmp->next = p->next;
    p->next = tmp;
}

void destory(list_t l)
{
    pos_t head = l;
    for (l = l->next;l;l = l->next)
        free_node(l);
    head->next = NULL;
}

pos_t header(list_t l)
{
    return l;
}

pos_t first(list_t l)
{
    return header(l)->next;
}

pos_t advance(pos_t p, list_t l)
{
    return find_previous(p->e, l);
}

element_t retrieve(pos_t p)
{
    return p->e;
}

void traversal(void (*visit)(node_t *p), list_t l)
{
    pos_t f = first(l);
    for (;f;f = f->next)
        visit(f);
}
