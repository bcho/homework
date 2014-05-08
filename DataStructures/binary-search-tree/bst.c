#include "bst.h"

#include <stdlib.h>
#include <stdio.h>

struct bst *bst_create(char data)
{
    struct bst *t;

    t = malloc(sizeof(struct bst));
    if (t == NULL)
        return NULL;
    t->data = data;
    t->lchild = NULL;
    t->rchild = NULL;

    return t;
}

struct bst *bst_init(int count, char *items)
{
    int i;
    struct bst *t;

    if (count <= 0)
        return NULL;

    t = bst_create(items[0]);
    for (i = 1; i < count; i++)
        bst_insert(&t, items[i]);

    return t;
}

void bst_destory(struct bst *t)
{
    if (t == NULL)
        return;

    bst_destory(t->lchild);
    bst_destory(t->rchild);
    free(t);
}

struct bst *bst_search(struct bst *t, char e)
{
    if (t == NULL)
        return NULL;

    if (t->data == e)
        return t;
    
    if (t->data > e)
        return bst_search(t->lchild, e);
    return bst_search(t->rchild, e);
}

struct bst *bst_insert_aux(struct bst *t, char e)
{
    struct bst *node;

    if (t == NULL) {
        node = bst_create(e);
        return node;
    }

    if (t->data > e)  // Should place in the left sub tree.
        t->lchild = bst_insert_aux(t->lchild, e);
    else if (t->data < e)  // Should place in the right sub tree.
        t->rchild = bst_insert_aux(t->rchild, e);
    return t;
}

void bst_insert(struct bst **t, char e)
{
    *t = bst_insert_aux(*t, e);
}

struct bst *bst_min(struct bst *t)
{
    if (t == NULL)
        return NULL;

    if (t->lchild == NULL)
        return t;
    return bst_min(t->lchild);
}

struct bst *bst_remove_min(struct bst *t)
{
    struct bst *p;

    if (t == NULL)
        return NULL;

    if (t->lchild == NULL) {
        p = t->rchild;
        t->lchild = NULL;
        t->rchild = NULL;
        bst_destory(t);

        return p;
    }

    t->lchild = bst_remove_min(t->lchild);
    return t;
}

struct bst *bst_remove_aux(struct bst *t, char e)
{
    struct bst *p;

    if (t == NULL)
        return NULL;

    if (t->data > e) {  // Should remove from left sub tree.
        t->lchild = bst_remove_aux(t->lchild, e);
        return t;
    } else if (t->data < e) {  // Should remove from right sub tree.
        t->rchild = bst_remove_aux(t->rchild, e);
        return t;
    }

    // Remove current node.
    if (t->rchild == NULL)  { // Replace with left child since right child is absent.
        p = t->lchild;
        t->lchild = NULL;
        t->rchild = NULL;
        bst_destory(t);

        return p;
    }
    if (t->lchild == NULL)  { // Replace with right child since left child is absent.
        p = t->rchild;
        t->lchild = NULL;
        t->rchild = NULL;
        bst_destory(t);

        return p;
    }

    // Replace with right sub tree's smallest node.
    p = t;
    t = bst_min(p->rchild);
    t->rchild = bst_remove_min(p->rchild);
    t->lchild = p->lchild;

    p->lchild = NULL;
    p->rchild = NULL;
    bst_destory(p);

    return t;
}

void bst_remove(struct bst **t, char e)
{
    *t = bst_remove_aux(*t, e);
}

void bst_prefix_print(struct bst *t)
{
    if (t == NULL)
        return;

    bst_prefix_print(t->lchild);
    printf("%c", t->data);
    bst_prefix_print(t->rchild);
}
