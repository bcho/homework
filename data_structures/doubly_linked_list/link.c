#include <stdio.h>
#include <stdlib.h>
#include "link.h"

node_t *new_node(void)
{
    node_t *t = malloc(sizeof(node_t));
    if (t == NULL)
        printf("Out of memory.");
    return t;
}

void free_node(node_t *n)
{
    free(n);
}

list_t *make_list(void)
{
    list_t *l = malloc(sizeof(list_t));
    l->head = new_node();
    l->tail = new_node();
    l->head->prev = NULL;
    l->head->next = l->tail;
    l->head->e = '\0';
    l->tail->prev = l->head;
    l->tail->next = NULL;
    l->tail->e = '\0';
    return l;
}

int is_empty(list_t l)
{
    return (l.head->next == l.tail);
}

int is_head(pos_t p, list_t l)
{
    return (p == l.head);
}

int is_last(pos_t p, list_t l)
{
    return (p == l.tail);
}

pos_t find(element_t x, list_t l)
{
    pos_t c = l.head;
    for (;c && c->e != x;c = c->next)
        ;
    return c;
}

node_t *pop(element_t x, list_t l)
{
    pos_t pre, cur;
    pre = find_previous(x, l);
    if (!is_last(pre, l)) {
        cur = pre->next;
        pre->next = cur->next;
        cur->next->prev = pre;
        cur->next = NULL;
        cur->prev = NULL;
        return cur;
    }
    return NULL;
}

pos_t find_previous(element_t x, list_t l)
{
    pos_t c = l.head;
    for (;c && c->next->e != x;c = c->next)
        ;
    return c;
}

void insert(element_t x, list_t l, pos_t p)
{
    node_t *n = new_node();
    n->e = x;
    n->prev = p;
    n->next = p->next;
    if (!is_last(p, l)) {
        p->next->prev = n;
    }
    p->next = n;
}

void destory(list_t l)
{
    pos_t c = first(l);
    for (;!is_last(c, l);c = c->next)
        free_node(c);
    free_node(l.head);
    free_node(l.tail);
    /* XXX free l
     * when tring to free(l) (l is list_t *),
     * malloc will raise `double free` exception
     */
}

pos_t header(list_t l)
{
    return l.head;
}

pos_t first(list_t l)
{
    return header(l)->next;
}

pos_t advance(pos_t p)
{
    return p->prev;
}

element_t retrieve(pos_t p)
{
    return p->e;
}

void traversal(void (*visit)(node_t *p), pos_t l, int reverse)
{
    for (;l;) {
        visit(l);
        if (reverse)
            l = l->prev;
        else
            l = l->next;
    }
}
