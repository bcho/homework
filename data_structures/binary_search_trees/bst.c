#include <stdlib.h>
#include <assert.h>
#include "bst.h"

struct tree_r {
    element_t element;
    tree_t left, right;
};

tree_t create_node(element_t x)
{
    tree_t node;
    node = malloc(sizeof(struct tree_r));
    assert(node != NULL);
    node->element = x;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_node(tree_t t)
{
    free(t);
}

tree_t create_tree(element_t l[], int len)
{
    int i;
    tree_t root;

    assert(len > 0);

    root = create_node(l[0]);
    for (i = 1;i < len;i++)
        insert_tree(l[i], root);
    return root;
}

void dispose_tree(tree_t t)
{
    if (t == NULL)
        return;
    if (t->left)
        dispose_tree(t->left);
    if (t->right)
        dispose_tree(t->right);
    free_node(t);
}

tree_t find(element_t x, tree_t t)
{
    if (t == NULL)
        return NULL;
    else if (retrieve(t) == x)
        return t;
    else if (retrieve(t) > x)
        return find(x, t->left);
    else if (retrieve(t) < x)
        return find(x, t->right);
}

tree_t find_min(tree_t t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return find_min(t->left);
}

tree_t find_max(tree_t t)
{
    if (t == NULL)
        return NULL;
    else if (t->right == NULL)
        return t;
    else
        return find_max(t->right);
}

tree_t insert_tree(element_t x, tree_t t)
{
    /* already in the bottom */
    if (t == NULL)
       t = create_node(x);
    else
    /* insert into left subtree or right subtree */
       if (retrieve(t) > x)
           t->left = insert_tree(x, t->left);
       else if (retrieve(t) <= x)
           t->right = insert_tree(x, t->right);

    /* let parent update their subtree */
    return t;
}

tree_t delete_tree(element_t x, tree_t t)
{
    tree_t tmp;

    /* x is not in the tree */
    assert(t != NULL);
    if (retrieve(t) > x)
        t->left = delete_tree(x, t->left);
    else if (retrieve(t) < x)
        t->right = delete_tree(x, t->right);
    /* this node has two children */
    else if (t->left && t->right) {
        /* replace this node with the smallest node(call it A) in
         * right subtree, because A is bigger than the biggest node
         * in the left subtree. Then the delete operation become
         * delete A in right subtree. */
        tmp = find_min(t->right);
        t->element = tmp->element;
        t->right = delete_tree(t->element, t->right);
    } else {
        tmp = t;
        /* if this node still has child, let it replace this node */
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        free_node(tmp);
    }
    
    /* let parent update their subtree */
    return t;
}

element_t retrieve(tree_t t)
{
    assert(t != NULL);
    return t->element;
}

void inorder_traversal(tree_t t, void (*visit)(tree_t x))
{
    if (t == NULL)
        return;
    if (t->left)
        inorder_traversal(t->left, visit);
    visit(t);
    if (t->right)
        inorder_traversal(t->right, visit);
}
