#include <stdlib.h>
#include "calculator.h"
#include "tree.h"

tree_t build_tree_node(element_t v, tree_t left, tree_t right)
{
    tree_t t = malloc(sizeof(struct tree_r));
    if (t == NULL)
        return NULL;
    t->value = v;
    t->left = left;
    t->right = right;
    return t;
}

void dispose_tree(tree_t t)
{
    if (t == NULL)
        return;
    if (t->left)
        dispose_tree(t->left);
    if (t->right)
        dispose_tree(t->right);
    free(t);
}

void inorder_traversal(tree_t t, void (*visit)(tree_t t))
{
    if (t == NULL)
        return;
    if (t->left)
        inorder_traversal(t, visit);
    visit(t);
    if (t->right)
        inorder_traversal(t, visit);
}
