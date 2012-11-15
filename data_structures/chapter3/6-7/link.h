#ifndef LINK_H
#define LINK_H

struct node;
typedef int element_t;
typedef struct node *node_ptr;
typedef struct node node_t;
typedef node_ptr list_t;
typedef node_ptr pos_t;

list_t make_list(void);
void destory(list_t l);
int is_empty(list_t l);
int is_last(pos_t p);
pos_t find(element_t x, list_t l);                                  /* find node with exp */
node_t *pop(element_t x, list_t l);
pos_t find_previous(node_t *x, list_t l);
void insert(element_t exp, element_t coe, pos_t p);                 /* insert new node after p */
pos_t header(list_t l);                                             /* return l's head */
element_t retrieve_exp(pos_t p);
element_t retrieve_coe(pos_t p);
void traversal(void (*visit)(node_t *p), list_t l);

/* polynomials */
struct node {
    element_t exp, coe;
    pos_t next;
};
typedef list_t polynomials_t;
#endif
