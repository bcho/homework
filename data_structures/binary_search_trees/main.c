#include <stdio.h>
#include <string.h>
#include "bst.h"

#define sep printf("\n")

void print_node(tree_t x);

int main()
{
    char _[] = "deadbeef";
    tree_t t = create_tree(_, strlen(_));

    inorder_traversal(t, print_node);
    sep;
    printf("%c %c %c", retrieve(find_min(t)), retrieve(find_max(t)),
                       retrieve(find('a', t)));
    sep;

    t = insert_tree('z', t);
    printf("%c %c %c", retrieve(find_min(t)), retrieve(find_max(t)),
                       retrieve(find('a', t)));
    sep;
    inorder_traversal(t, print_node);
    sep;
    
    delete_tree('z', t);
    printf("%c %c %c", retrieve(find_min(t)), retrieve(find_max(t)),
                       retrieve(find('a', t)));
    sep;
    inorder_traversal(t, print_node);

    dispose_tree(t);

    return 0;
}

void print_node(tree_t x)
{
    printf("%c", retrieve(x));
}
