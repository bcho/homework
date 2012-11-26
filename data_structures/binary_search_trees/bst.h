#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef char element_t;
struct tree_r;
typedef struct tree_r *tree_t;

/* create a tree from a list */
tree_t create_tree(element_t l[], int len);
void dispose_tree(tree_t t);
tree_t find(element_t x, tree_t t);
tree_t find_min(tree_t t);
tree_t find_max(tree_t t);
tree_t insert_tree(element_t x, tree_t t);
tree_t delete_tree(element_t x, tree_t t);
element_t retrieve(tree_t t);

void inorder_traversal(tree_t t, void (*visit)(tree_t x));
#endif
