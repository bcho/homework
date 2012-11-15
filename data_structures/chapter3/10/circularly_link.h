#ifndef CIRCULARLY_LINK_H
#define CIRCULARLY_LINK_H

typedef int element_t;
struct node {
    element_t num;
    struct node *next;
};
typedef struct node *pos_t;
struct link {
    struct node *head;
    struct node *cur;
    element_t length;
};
typedef struct link *circularly_link_t;

circularly_link_t make_list();
void dispose_list(circularly_link_t l);
element_t retrieve(pos_t n);
pos_t head(circularly_link_t l);
pos_t current(circularly_link_t l);
int is_last(pos_t n, circularly_link_t l);
int is_empty(circularly_link_t l);
/* move list forward */
void forward(circularly_link_t l);
void pop(pos_t n, circularly_link_t l);
void insert(element_t x, pos_t n, circularly_link_t l);
/* reset current to head */
void reset(circularly_link_t l);
void traversal(void (*visit)(pos_t n), circularly_link_t l);
#endif
