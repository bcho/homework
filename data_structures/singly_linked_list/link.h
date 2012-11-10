#ifndef LINK_H
#define LINK_H

struct node;
typedef char element_t;
typedef struct node *node_ptr;
typedef struct node node_t;
typedef node_ptr list_t;
typedef node_ptr pos_t;

list_t make_list(void);
int is_empty(list_t l);
int is_last(pos_t p, list_t l);
pos_t find(element_t x, list_t l);
node_t *pop(element_t x, list_t l);
pos_t find_previous(element_t x, list_t l);
void insert(element_t x, list_t l, pos_t p);
void destory(list_t l);
pos_t header(list_t l);
pos_t first(list_t l);                          /* get first element of l */
pos_t advance(pos_t p, list_t l);               /* move forward */
element_t retrieve(pos_t p);                    /* get element of p */
void traversal(void (*visit)(node_t *p), list_t l);

/* singly linked list */
struct node {
    element_t e;
    pos_t next;
};
#endif
