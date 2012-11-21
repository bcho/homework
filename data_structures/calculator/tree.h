#ifndef TREE_H
#define TREE_H

#include "calculator.h"

typedef token_t element_t;
struct tree_r {
    element_t value;
    struct tree_r *left, *right;
};
typedef struct tree_r *tree_t;

tree_t build_tree_node(element_t v, tree_t left, tree_t right);
void dispose_tree(tree_t t);

void inorder_traversal(tree_t t, void (*visit)(tree_t t));
#endif
