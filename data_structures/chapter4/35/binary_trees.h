#ifndef BINARY_TREES
#define BINARY_TREES

typedef char element_t;
struct binary_tree_r {
    element_t value;
    struct binary_tree_r *left, *right;
};
typedef struct binary_tree_r *binary_tree_t;

/* assumes that: i is parent, i * 2 and i * 2 + 1 are children,
 * and BLANK_NODE means this node is not exist.
 * */
binary_tree_t create_tree(char nodes[], int length);
void dispose_tree(binary_tree_t t);

int tree_height(binary_tree_t t);

void preorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t));
void inorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t));
void postorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t));
void levelorder_traversal(binary_tree_t t, void (*visit)(binary_tree_t t));

#define MAX_TREE_NODE 1000
#define BLANK_NODE 0
#endif
