#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define PANIC(reason) \
    do { \
        fprintf(stderr, reason); \
        exit(-1); \
    } while (0)


// 遍历一个链表
//
// @param 循环变量
// @param 链表头
#define llist_for_each(pos, head) \
    for (pos = (head); pos != NULL; pos = pos->next)

// 插入一个结点到指定结点之后
//
// @param 指定结点
// @param 插入结点
#define llist_insert_after(before, node) \
    do { \
        (node)->next = (before)->next; \
        (before)->next = node; \
    } while (0)


// 从链表中弹出一个结点
//
// @param 弹出结点前继
// @param 待弹出结点
#define llist_pop(prev, node) \
    do { \
        node = (prev)->next; \
        if (node != NULL) { \
            (prev)->next = node->next; \
            node->next = NULL; \
        } \
    } while (0)

#endif  /* #ifndef UTILS_H */
