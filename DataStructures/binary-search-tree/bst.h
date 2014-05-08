#ifndef BST_H
#define BST_H


struct bst {
    char data;
    struct bst *lchild;
    struct bst *rchild;
};

struct bst *bst_init(int, char *);
void bst_destory(struct bst *);

struct bst *bst_search(struct bst *, char);
void bst_insert(struct bst **, char);
void bst_remove(struct bst **, char);

void bst_prefix_print(struct bst *);


#endif
