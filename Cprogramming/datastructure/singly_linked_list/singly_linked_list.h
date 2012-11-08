#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

typedef char element_t;

struct node {
    element_t e; // element
    struct node *next;
};
typedef struct node node_t;

node_t *make_node(element_t e); // create a new node
void free_node(node_t *n);  // free a node
node_t *create(element_t *e);  // create a new link
int destory(node_t *link);  // destory a link
/* XXX TRICKS 
 * Passing `node_t *link` to the func means the func will
 * get the pointer of node_t, but you cannot modify the `link`.
 * (actually `link` is `node_t *`, but we can suppose it as a
 * type called `link_t`, and we should use `*link_t` if we
 * want to modify it in the func scope.)
 *
 * */
node_t *pop(node_t **link);  // pop the head element
int push(node_t *link, node_t *x);  // append an element to tail
node_t *search(node_t *link, element_t key);  // search an element
void traverse(node_t *link, void (*visit)(node_t));  // visit each element

#endif
