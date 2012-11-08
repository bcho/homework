#include <stdio.h>
#include <stdlib.h>
#include "singly_linked_list.h"

node_t *make_node(element_t e)
{
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL)
        printf("Out of memory.");
    new->e = e;
    return new;
}

void free_node(node_t *n)
{
    free(n);
}

node_t *create(element_t *e)
{
    node_t *node, *head = NULL;
    if (e) {
        head = make_node(*(e++));
        head->next = NULL;
    }
    node = head;
    for (;*e != '\0';e++) {
        node->next = make_node(*e);
        node = node->next;
    }
    node->next = NULL;
    return head;
}

int destory(node_t *link)
{
    for (;link;link = link->next)
        free_node(link);
    return 1;
}

node_t *pop(node_t **link)
{
    node_t *h = *link;
    *link = (*link)->next;
    h->next = NULL;
    return h;
}

int push(node_t *link, node_t *x)
{
    // if link is NULL
    if (!link) {
        x->next = NULL;
        link = x;
        return 1;
    }
    for (;link->next;link = link->next)
        ;
    x->next = NULL;
    link->next = x;
    return 1;
}

node_t *search(node_t *link, element_t key)
{
    for (;link && link->e != key;link = link->next)
        ;
    // found
    if (link->e == key)
        return link;
    // not found
    return NULL;
}

void traverse(node_t *link, void (*visit)(node_t))
{
    for (;link;link = link->next)
        visit(*link);
}
