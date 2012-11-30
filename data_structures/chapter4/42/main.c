#include <stdio.h>
#include <string.h>
#include "binary_trees.h"

#define MAX 100
#define N_CHILDREN 2

#define sep printf("\n")
    
typedef struct {
    element_t value;
    int level;
} tree_node;

int is_isomorphic(binary_tree_t a, binary_tree_t b);
void print(binary_tree_t n);

int main()
{
    char a[MAX] = " abcdegf";
    char b[MAX] = " acbfged";

    binary_tree_t ta = create_tree(a, strlen(a));
    binary_tree_t tb = create_tree(b, strlen(b));

    inorder_traversal(ta, print);
    sep;
    inorder_traversal(tb, print);
    sep;

    printf("%d", is_isomorphic(ta, tb));

    return 0;
}

void print(binary_tree_t n)
{
    printf("%c ", n->value);
}

/* do a level-order traversal to t, and get its size 
 * preorder and inorder will be simpler
 * */
int levelorder_visit(binary_tree_t t, tree_node nodes[], int reverse)
{
    binary_tree_t tree[MAX], child[N_CHILDREN];      /* for n-children tree, change it to n */
    int front, tail, size, i;
    
    if (t == NULL)
        return 0;

    front = 0; tail = 0; size = 1;
    tree[tail] = t;
    nodes[tail].value = t->value; nodes[tail].level = 1;
    for (;front <= tail;front++) {
        /* from right to left */
        if (reverse) {
            child[0] = tree[front]->right;
            child[1] = tree[front]->left;
        } else {
            child[0] = tree[front]->left;
            child[1] = tree[front]->right;
        }
        for (i = 0;i < N_CHILDREN;i++)
            if (child[i]) {
                size++;
                tree[++tail] = child[i];
                nodes[tail].value = child[i]->value;
                nodes[tail].level = nodes[front].level + 1;
            }
    }

    return size;
}

/* time complexity: O(n + n + n) = O(n)
 * but I have no idea about how to deal with **some of the**
 * */
int is_isomorphic(binary_tree_t a, binary_tree_t b)
{
    tree_node ta[MAX], tb[MAX];
    int sizea, sizeb, i;

    sizea = levelorder_visit(a, ta, 0);
    sizeb = levelorder_visit(b, tb, 1);

    if (sizea != sizeb)
        return 0;

    for (i = 0;i < sizea;i++)
        if (ta[i].value != tb[i].value || ta[i].level != tb[i].level)
            return 0;
    return 1;
}
