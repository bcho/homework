#include <stdio.h>
#include "binary_trees.h"

#define sep printf("\n")

void print_node(binary_tree_t t);

int main()
{
    char msg[] = " deadbeef";
    binary_tree_t t = create_tree(msg, 8);

    printf("%d", tree_height(t));
    sep;

    preorder_traversal(t, print_node);
    sep;
    postorder_traversal(t, print_node);
    sep;
    inorder_traversal(t, print_node);
    sep;
    levelorder_traversal(t, print_node);

    return 0;
}

void print_node(binary_tree_t t)
{
    printf("%c ", t->value);
}
