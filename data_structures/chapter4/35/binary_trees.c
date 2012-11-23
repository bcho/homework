#include <stdlib.h>
#include <assert.h>
#include "binary_trees.h"

#define max(a, b) ((a) > (b)) ? (a) : (b)

binary_tree_t make_node(element_t c)
{
    binary_tree_t t = malloc(sizeof(struct binary_tree_r));
    if (t == NULL)
        return NULL;
    t->value = c;
    t->left = NULL;
    t->right = NULL;
    return t;
}

binary_tree_t create_tree(char nodes[], int length)
{
    int i;
    binary_tree_t tree_nodes[MAX_TREE_NODE];
    /* root is at 1 */
    for (i = 1;i <= length;i++)
        if (nodes[i] != BLANK_NODE)
            tree_nodes[i] = make_node(nodes[i]);
        else
            tree_nodes[i] = NULL;
    /* link the tree */
    for (i = 1;i <= length / 2;i++)
        if (nodes[i] != BLANK_NODE) {
            if (i * 2 <= length)
                tree_nodes[i]->left = tree_nodes[i * 2];
            if (i * 2 + 1 <= length)
                tree_nodes[i]->right = tree_nodes[i * 2 + 1];
        }
    return tree_nodes[1];
}

void dispose_tree(binary_tree_t t)
{
    if (t == NULL)
        return;
    if (t->left)
        dispose_tree(t->left);
    if (t->right)
        dispose_tree(t->right);
    free(t);
}

int tree_height(binary_tree_t t)
{
    if (t == NULL)
        return 0;
    return max(tree_height(t->left), tree_height(t->right)) + 1;
}

void preorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t))
{
    if (t == NULL)
        return;
    visit(t);
    if (t->left)
        preorder_traversal(t->left, visit);
    if (t->right)
        preorder_traversal(t->right, visit);
}

void inorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t))
{
    if (t == NULL)
        return;
    if (t->left)
        inorder_traversal(t->left, visit);
    visit(t);
    if (t->right)
        inorder_traversal(t->right, visit);
}

void postorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t))
{
    if (t == NULL)
        return;
    if (t->left)
        postorder_traversal(t->left, visit);
    if (t->right)
        postorder_traversal(t->right, visit);
    visit(t);
}

static int next(int current, int size)
{
    return (current + 1) % size;
}

/* time complexity: O(n), where n is t's nodes count */
void levelorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t))
{
    binary_tree_t queue[MAX_TREE_NODE];
    int front, tail, length;

    if (t == NULL)
        return;
    front = -1, tail = 0, length = 1;
    queue[(front = next(front, MAX_TREE_NODE))] = t;
    for (;length;front = next(front, MAX_TREE_NODE), length--) {
        visit(queue[front]);
        if (queue[front]->left) {
            tail = next(tail, MAX_TREE_NODE);
            queue[tail] = queue[front]->left;
            length++;
        }
        if (queue[front]->right) {
            tail = next(tail, MAX_TREE_NODE);
            queue[tail] = queue[front]->right;
            length++;
        }
    }
}
