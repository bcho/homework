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
    list_t l = malloc(sizeof(list_t));
    if (l == NULL) {
        printf("Out of memory!");
    } else {
        l->header = new_node();
        l->header->next = NULL;
        l->current = l->header;
    }
    return l;
}

int is_empty(list_t l)
{
    return (l->current == l->header);
}

int is_last(pos_t p, list_t l)
{
    return p->next == NULL;
}

pos_t find(element_t x, list_t l)
{
    pos_t cur = l->current;
    for (;cur && cur->e != x;cur = cur->next)
        ;
    return cur;
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
    pos_t cur = l->header->next;
    for (;cur && cur->next->e != x;cur = cur->next)
        ;
    return cur;
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
    pos_t cur = header(l)->next;
    pos_t tmp;
    for (;cur;) {
        tmp = cur;
        cur = cur->next;
        free_node(tmp);
    }
    free_node(l->header);
    free(l);
}

pos_t header(list_t l)
{
    return l->header;
}

pos_t current(list_t l)
{
    return l->current;
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
    pos_t f = header(l)->next;
    for (;f;f = f->next)
        visit(f);
}
