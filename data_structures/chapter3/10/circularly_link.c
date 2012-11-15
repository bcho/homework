#include <stdlib.h>
#include <stdio.h>
#include "circularly_link.h"

#define MEMORY_OUT "Out of memory!"

circularly_link_t make_list()
{
    circularly_link_t l = malloc(sizeof(struct link));
    if (l == NULL) {
        printf(MEMORY_OUT);
        return NULL;
    }
    l->head = malloc(sizeof(struct node));
    if (l->head == NULL) {
        printf(MEMORY_OUT);
        return NULL;
    }
    l->head->next = l->head;
    l->cur = l->head;
    l->length = 0;
    return l;
}

void dispose_list(circularly_link_t l)
{
    pos_t i, tmp;
    reset(l);
    forward(l);
    for (i = current(l);!is_last(i, l);i = current(l)) {
        tmp = i;
        forward(l);
        free(tmp);
    }
    free(head(l));
    free(l);
}

element_t retrieve(pos_t n)
{
    return n->num;
}

pos_t head(circularly_link_t l)
{
    return l->head;
}

pos_t current(circularly_link_t l)
{
    return l->cur;
}

int is_last(pos_t n, circularly_link_t l)
{
    return (n->next == head(l));
}

int is_empty(circularly_link_t l)
{
    return (l->length <= 0);
}

void forward(circularly_link_t l)
{
    /* move list current forward, also skip the head */
    do {
        l->cur = l->cur->next;
    } while (l->cur == head(l));
}

pos_t find_previous(pos_t n, circularly_link_t l)
{
    pos_t i;
    for (i = head(l);i->next != n && !is_last(i, l);i = i->next)
        ;
    if (i->next == n || (is_last(i, l) && head(l) == n))
        return i;
    return NULL;
}

void pop(pos_t n, circularly_link_t l)
{
    pos_t prev = find_previous(n, l);
    if (prev) {
        prev->next = n->next;
        if (n == head(l))
            l->head = n->next;
        if (n == current(l))
            forward(l);
        l->length--;
        free(n);
    }
}

void insert(element_t x, pos_t n, circularly_link_t l)
{
    struct node *e = malloc(sizeof(struct node));
    if (e == NULL) {
        printf(MEMORY_OUT);
        return;
    }
    e->num = x;
    e->next = n->next;
    n->next = e;
    l->length++;
}

void reset(circularly_link_t l)
{
    l->cur = l->head;
}

void traversal(void (*visit)(pos_t n), circularly_link_t l)
{
    if (is_empty(l))
        return;
    pos_t i;
    for (i = head(l)->next;!is_last(i, l);i = i->next)
        visit(i);
    /* visit the last node */
    visit(i);
}
