/* linked_tree.c: 链树实现 */

#include "assert.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 结构体定义 */
struct tree {
    char *data;
    
    struct tree *parent;
    struct tree *left_child;
    struct tree *right_sibling;
};

/* 访问函数定义 */
typedef void (*visitor_t)(struct tree *);

/* ADT 清单 */

/* 
 * 创建并初始化一棵空树
 *
 * :rtype: struct tree *
 */
struct tree *tree_init();

/* 
 * 销毁一棵树及其所有子结点
 *
 * :param t: 被销毁的树
 */
void tree_destory(struct tree *t);

/*
 * 将一棵树置为空树
 *
 * .. warning:: 不释放子树节点
 *
 * :param t: 被置空的树
 */
void tree_clear(struct tree *t);

/*
 * 检测树是否为空
 *
 * .. note:: 时间复杂度为 O(1)
 *
 * :param t: 被检测的树
 * :rtype:  0 为非空，否则为空
 */
int tree_is_empty(struct tree *t);

/*
 * 获取结点的值
 *
 * :param t: 传入的结点
 * :rtype: 返回的是结点值的头地址
 */
char *tree_value(struct tree *t);

/*
 * 对结点进行赋值
 *
 * .. note:: 会复制传入的值到结点上
 *
 * :param t: 传入的结点
 * :param data: 传入的值
 */
void tree_assign(struct tree *t, char *data);

/*
 * 向树插入新结点到第 i 位
 *
 * .. note:: 时间复杂度为 O(n)
 * .. note:: 子结点从 0 开始编号，如果插入位置小于 0 则插入到最开始，
 *           如果插入位置大于子结点总数，插入到最末端
 *
 * :param t: 传入的树
 * :param child: 传入的新结点
 * :param i: 插入的位置
 */
void tree_insert_child(struct tree *t, struct tree *child, int i);

/*
 * 从树中删除并返回第 i 个结点
 *
 * .. note:: 时间复杂度为 O(n)
 * .. note:: 子结点从 0 开始编号，如果删除位置不存在则返回 NULL
 *
 * :param t: 传入的树
 * :param i: 删除结点的位置
 * :rtype: struct tree *
 */
struct tree *tree_delete_child(struct tree *t, int i);

/*
 * 计算树的深度
 *
 * :param t: 被计算的树
 * :rtype: 树的深度
 */
int tree_depth(struct tree *t);

/*
 * 获取树的根
 *
 * .. note:: 如果传入的结点不是树根，
 *           则返回它的父结点的树根
 *
 * :param t: 传入的树
 * :rtype: 树根结点
 */
struct tree *tree_root(struct tree *t);

/*
 * 获取结点的父结点
 *
 * .. note:: 若当前结点没有父节点，返回它本身
 *
 * :param t: 传入的结点
 * :rtype: struct tree *
 */
struct tree *tree_parent(struct tree *t);

/*
 * 获取结点的左儿子
 *
 * .. note:: 若当前结点没有左儿子，返回 NULL
 *
 * :param t: 传入的结点
 * :rtype: struct tree *
 */
struct tree *tree_left_child(struct tree *t);

/*
 * 获取结点的右兄弟
 *
 * .. note:: 若当前结点没有右儿子，返回 NULL
 *
 * :param t: 传入的结点
 * :rtype: struct tree *
 */
struct tree *tree_right_sibling(struct tree *t);

/*
 * 对树执行先根遍历
 *
 * :param t: 被遍历的树
 * :param visitor: 遍历函数指针
 */
void tree_traverse_pre_root(struct tree *t, visitor_t visitor);

/*
 * 对树执行后根遍历
 *
 * :param t: 被遍历的树
 * :param visitor: 遍历函数指针
 */
void tree_traverse_post_root(struct tree *t, visitor_t visitor);

/*
 * 从字符串定义创建一棵树
 *
 * .. seealso:: TODO 字符串定义
 *
 * :param s: 字符串定义
 * :rtype: struct tree *
 */
struct tree *tree_from_string(char *s);

/*
 * 生成树的字符串形式 
 *
 * .. warning:: 返回的字符串是从堆分配的内存，
 *              使用后需要手动 free 回收
 *
 * :param t: 传入的树
 * :rtype: char *
 */
char *tree_stringify(struct tree *t);

/*
 * 将树转换成二叉树
 *
 * .. note:: 返回的是新树的指针
 *
 * :param t: 传入的树
 * :rtype: struct tree *
 */
struct tree *tree_to_binary(struct tree *t);


/* 测试程序 */
int main()
{
    struct tree *t, *c1, *c2;

    /* test init */
    t = tree_init();
    assert(t != NULL);
    /* Should be an empty tree */
    assert(tree_depth(t) == 0);
    assert(tree_is_empty(t));
    tree_destory(t);

    /* test assign */
    t = tree_init();
    tree_assign(t, "hello");
    /* Should not be an empty tree */
    assert(tree_depth(t) == 1);
    assert(tree_is_empty(t) == 0);
    /* Should have same value */
    assert(strcmp("hello", tree_value(t)) == 0);
    tree_destory(t);

    /* test tree root & parent */
    t = tree_init();
    tree_assign(t, "hello");
    assert(tree_root(t) == t);
    assert(tree_parent(t) == t);
    tree_destory(t);

    /* test tree insert */
    t = tree_init();
    tree_assign(t, "hello");
    c1 = tree_init();
    c2 = tree_init();
    tree_assign(c1, "world");
    tree_assign(c2, "world!");
    /* test insert in the head */
    tree_insert_child(t, c1, -1);
    /* test insert in the tail */
    tree_insert_child(t, c2, 10);
    assert(tree_left_child(t) == c1);
    assert(tree_right_sibling(c1) == c2);
    tree_destory(t);

    /* test tree delete */
    t = tree_init();
    tree_assign(t, "hello");
    c1 = tree_init();
    c2 = tree_init();
    tree_assign(c1, "world");
    tree_assign(c2, "world!");
    tree_insert_child(t, c1, 0);
    tree_insert_child(c1, c2, 0);
    assert(tree_depth(t) == 3);
    assert(tree_depth(c1) == 2);
    assert(tree_depth(c2) == 1);
    assert(tree_delete_child(c1, 0) == c2);
    assert(tree_depth(t) == 2);
    assert(tree_depth(c1) == 1);
    tree_destory(t);

    /* test tree from string */
    t = tree_from_string("(A)");
    assert(tree_depth(t) == 1);
    assert(strcmp(tree_value(t), "A") == 0);
    assert(strcmp(tree_stringify(t), "(A)") == 0);
    tree_destory(t);
    
    t = tree_from_string("(A (B))");
    assert(tree_depth(t) == 2);
    assert(strcmp(tree_value(t), "A") == 0);
    assert(strcmp(tree_stringify(t), "(A(B))") == 0);
    tree_destory(t);
    
    t = tree_from_string("(A(B(D)(E))(C (F )))");
    assert(tree_depth(t) == 3);
    assert(strcmp(tree_value(t), "A") == 0);
    assert(strcmp(tree_stringify(t), "(A(B(D)(E))(C(F)))") == 0);
    tree_destory(t);

    return 0;
}

char *Malloc(size_t size)
{
    char *buffer;

    if ((buffer = malloc(size)) == NULL)
        exit(-1);
    return buffer;
}

char *Realloc(char *ptr, size_t size)
{
    return realloc(ptr, size);
}

char *str_copy(char *str)
{
    int size;
    char *buffer;

    size = strlen(str);
    buffer = Malloc(sizeof(char) * (size + 1));
    strncpy(buffer, str, size);
    buffer[size] = '\0';

    return buffer;
}

char *str_copyn(char *str, int n)
{
    char *buffer;

    buffer = Malloc(sizeof(char) * (n + 1));
    strncpy(buffer, str, n);
    buffer[n] = '\0';

    return buffer;
}

int str_startswith(char *str, char prefix)
{
    return *str == prefix;
}

int str_endswith(char *str, char suffix)
{
    return *(str + strlen(str) - 1) == suffix;
}

int str_split(char *str, char *delim, char ***rv)
{
    int count;
    char *c;
    char **tokens;

    tokens = malloc(sizeof(char *) * 0);
    c = strtok(str, delim);
    while (c != NULL) {
        count = count + 1;
        tokens = (char **) Realloc((char *) tokens, sizeof(char *) * count);
        tokens[count - 1] = str_copy(c);

        c = strtok(NULL, delim);
    }

    *rv = tokens;
    return count;
}

char *str_replace(char *from, char *pattern, char *replace)
{
    char *rv;
    char *p, *q, *r;
    int from_len, count, rv_len, pattern_len, replace_len;

    from_len = strlen(from);
    pattern_len = strlen(pattern);
    replace_len = strlen(replace);

    for (count = 0, p = from;
         (q = strstr(p, pattern)) != NULL;
         p = q + pattern_len, count++)
        ;
    rv_len = from_len + count * (replace_len - pattern_len);

    rv = Malloc(sizeof(char) * (rv_len + 1));

    for (r = rv, p = from;
         (q = strstr(p, pattern)) != NULL;
         p = q + pattern_len) {
        memcpy(r, p, q - p);
        r = r + (q - p);
        memcpy(r, replace, replace_len);
        r = r + replace_len;
    }
    strcpy(r, p);

    return rv;
}

struct tree *tree_init()
{
    struct tree *t;

    t = (struct tree *) Malloc(sizeof(struct tree));
    t->data = NULL;
    t->parent = NULL;
    t->left_child = NULL;
    t->right_sibling = NULL;

    return t;
}

void tree_destory(struct tree *t)
{
    struct tree *p;
    struct tree *next;

    if (t == NULL)
        return;

    for (p = tree_left_child(t), next = NULL; p != NULL; p = next) {
        next = tree_right_sibling(p);
        tree_destory(p);
    }

    free(t->data);
    free(t);
}

void tree_clear(struct tree *t)
{
    if (t != NULL) {
        free(t->data);
        t->left_child = NULL;
    }
}

int tree_is_empty(struct tree *t)
{
    return ((t == NULL) ||
            (t->data == NULL && tree_left_child(t) == NULL));
}

char *tree_value(struct tree *t)
{
    if (t == NULL)
        return NULL;
    return t->data;
}

void tree_assign(struct tree *t, char *data)
{
    if (t == NULL || data == NULL)
        return;
    
    t->data = str_copy(data);
}

void tree_insert_child(struct tree *t, struct tree *child, int i)
{
    int j;
    struct tree fake;
    struct tree *p;

    if (i < 0)
        i = 0;

    for (fake.right_sibling = tree_left_child(t), p = &fake, j = 0;
         j < i && tree_right_sibling(p) != NULL;
         p = tree_right_sibling(p), j++)
        ;

    child->right_sibling = tree_right_sibling(p);
    p->right_sibling = child;
    p->parent = t;
    t->left_child = tree_right_sibling(&fake);
}

struct tree *tree_delete_child(struct tree *t, int i)
{
    int j;
    struct tree fake;
    struct tree *p, *rv;

    if (i < 0)
        return NULL;

    for (fake.right_sibling = tree_left_child(t), p = &fake, j = 0;
         j < i && p != NULL;
         p = tree_right_sibling(p), j++)
        ;

    if (p == NULL)
        return NULL;

    rv = p->right_sibling;
    if (rv != NULL) {
        p->right_sibling = rv->right_sibling;

        /* 删除关联结点 */
        rv->parent = NULL;
        rv->right_sibling = NULL;
    }

    t->left_child = tree_right_sibling(&fake);

    return rv;
}

int tree_depth(struct tree *t)
{
    struct tree *p;
    int max_depth, sub_depth;

    if (t == NULL || tree_is_empty(t))
        return 0;

    for (p = tree_left_child(t), max_depth = 0;
         p != NULL;
         p = tree_right_sibling(p)) {
        sub_depth = tree_depth(p);
        if (sub_depth > max_depth)
            max_depth = sub_depth;
    }

    return max_depth + 1;
}

struct tree *tree_root(struct tree *t)
{
    struct tree *parent;

    if (t == NULL)
        return NULL;

    /* 一直获取它的父结点直到树根 */
    while ((parent = tree_parent(t)) != t)
        t = parent;

    return t;
}

struct tree *tree_parent(struct tree *t)
{
    if (t == NULL)
        return NULL;

    if (t->parent == NULL)
        return t;
    return t->parent;
}

struct tree *tree_left_child(struct tree *t)
{
    if (t == NULL)
        return NULL;

    return t->left_child;
}

struct tree *tree_right_sibling(struct tree *t)
{
    if (t == NULL)
        return NULL;

    return t->right_sibling;
}

void tree_traverse_pre_root(struct tree *t, visitor_t visitor)
{
    struct tree *p;

    if (t == NULL)
        return;

    visitor(t);

    for (p = tree_left_child(t); p != NULL; p = tree_right_sibling(p))
        tree_traverse_pre_root(p, visitor);
}

void tree_traverse_post_root(struct tree *t, visitor_t visitor)
{
    struct tree *p;

    if (t == NULL)
        return;

    for (p = tree_left_child(t); p != NULL; p = tree_right_sibling(p))
        tree_traverse_pre_root(p, visitor);
    
    visitor(t);
}

struct queue {
    char **buffer;
    int l, r;
};

char *queue_pop(struct queue *q)
{
    char *rv;

    assert(q->r - q->l >= 0);
    rv = q->buffer[q->l];
    q->l = q->l + 1;

    return rv;
}

char *queue_first(struct queue *q)
{
    assert(q->r - q->l >= 0);
    return q->buffer[q->l];
}

void queue_enqueue(struct queue *q, char *value)
{
    q->r = q->r + 1;
    q->buffer[q->r] = str_copy(value);
}

struct queue *queue_init(char **values, int count)
{
    int i;
    struct queue *q;
    
    q = (struct queue *) Malloc(sizeof(struct queue));
    q->l = 0;
    q->r = -1;
    q->buffer = (char **) Malloc(sizeof(char *) * count);
    for (i = 0; i< count; i++)
        queue_enqueue(q, values[i]);

    return q;
}

void queue_destory(struct queue *q)
{
    int i;

    for (i = 0; i < q->r; i++)
        free(q->buffer[i]);
    free(q->buffer);
}

struct queue *tokenize(char *s)
{
    int tokens_count, i;
    char *replaced;
    char **tokens;
    struct queue *q;

    replaced = str_replace(s, "(", " ( ");
    s = replaced;
    replaced = str_replace(s, ")", " ) ");
    free(s);
    s = replaced;
    tokens_count = str_split(s, " ", &tokens);
    free(s);

    q = queue_init(tokens, tokens_count);
    for (i = 0; i < tokens_count; i++)
        free(tokens[i]);
    free(tokens);

    return q;
}

struct tree *read_from(struct queue *tokens)
{
    int has_root, child_count;
    char *token;
    struct tree *node, *child;

    token = queue_pop(tokens);
    if (strcmp(token, "(") == 0) {
        node = tree_init();
        has_root = 0;
        child_count = 0;
        while (strcmp(queue_first(tokens), ")")) {
            child = read_from(tokens);
            if (!has_root) {
                has_root = 1;
                tree_assign(node, tree_value(child));
                tree_destory(child);
            } else {
                tree_insert_child(node, child, child_count);
                child_count = child_count + 1;
            }
        }
        queue_pop(tokens);
        return node;
    } else if (strcmp(token, ")") == 0) {
        assert(0);
    } else {
        node = tree_init();
        tree_assign(node, str_copy(token));
        return node;
    }
}

struct tree *tree_from_string(char *s)
{
    struct queue *tokens;
    struct tree *t;

    tokens = tokenize(s);
    t = read_from(tokens);
    queue_destory(tokens);
    
    return t;
}

void print_node(struct tree *t)
{
    printf("%s", tree_value(t));
}

char *tree_stringify(struct tree *t)
{
    int size;
    char *rv, *child;
    struct tree *p;

    if (t == NULL)
        return NULL;

    size = 2 + strlen(tree_value(t)) + 1;
    rv = Malloc(sizeof(char) * size);
    rv = str_copy("(");
    strcat(rv, tree_value(t));

    for (p = tree_left_child(t); p != NULL; p = tree_right_sibling(p)) {
        child = tree_stringify(p);
        if (child == NULL)
            continue;
        size = size + strlen(child);
        rv = Realloc(rv, sizeof(char) * size);
        strcat(rv, child);
        free(child);
    }
    strcat(rv, ")");

    return rv;
}
