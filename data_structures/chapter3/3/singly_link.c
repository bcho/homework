#include <stdio.h>
#include <stdlib.h>
#include "singly_link.h"

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
    list_t l = new_node();
    l->next = NULL;
    return l;
}

void destory(list_t l) {
    pos_t children;
    node_t *tmp;
    for (children = header(l)->next;children != NULL;) {
        tmp = children;
        children = children->next;
        free_node(tmp);
    }
    free_node(header(l));
}

int is_empty(list_t l)
{
    return (l->next == NULL);
}

int is_last(pos_t p)
{
    return (p->next == NULL);
}

pos_t find(element_t x, list_t l)
{
    pos_t cur;
    for (cur = header(l);!is_last(cur) && retrieve(cur) != x;cur = cur->next)
        ;
    if (retrieve(cur) == x)
        return cur;
    return NULL;
}

node_t *pop(element_t x, list_t l)
{
    node_t *p = find(x, l);
    pos_t prev;
    if (p) {
        prev = find_previous(p, l);
        prev->next = p->next;
    }
    return p;
}

pos_t find_previous(node_t *x, list_t l)
{
    pos_t cur;
    for (cur = header(l);cur->next && cur->next != x; cur = cur->next)
        ;
    if (cur->next == x)
        return cur;
    return NULL;
}

void insert(element_t x, pos_t p)
{
    node_t *c = new_node();
    c->e = x;
    c->next = p->next;
    p->next = c;
}

pos_t header(list_t l)
{
    return l;
}

element_t retrieve(pos_t p)
{
    return p->e;
}

void traversal(void (*visit)(node_t *p), list_t l)
{
    pos_t cur;
    for (cur = header(l)->next;cur;cur = cur->next)
        visit(cur);
}

void swap(pos_t a, pos_t b, list_t l)
{
    if (a == header(l) || b == header(l)) {
        printf("Swapping header is not allowed!");
    }
    pos_t prev_a, prev_b, tmp;
    prev_a = find_previous(a, l);
    prev_b = find_previous(b, l);
    prev_a->next = b;
    prev_b->next = a;
    tmp = a->next;
    a->next = b->next;
    b->next = tmp;
}
