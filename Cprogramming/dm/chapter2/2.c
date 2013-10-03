#include "link_list.h"

#include <stdio.h>
#include <stdlib.h>

void DeleteAndInsertSub(LinkList *la, LinkList *lb, int i, int j, int len)
{
    int k;
    LNode dummya, dummyb;
    LinkList preva, prevb;
    LNode *p;

    dummya.next = *la;
    dummyb.next = *lb;
    for (k = 0, preva = &dummya;k < i - 1 && preva;k++)
        // 获取到 i - 1
        preva = preva->next;
    for (k = 0, prevb = &dummyb;k < j - 1 && prevb && prevb->next;k++)
        // 获取到 j - 1
        prevb = prevb->next;

    for (k = 0;k < len;k++) {
        p = preva->next;
        preva->next = p->next;
        p->next = prevb->next;
        prevb->next = p;
        prevb = p;
    }
    *la = dummya.next;
    *lb = dummyb.next;
}

void Insert(LinkList *L, int i, char b)
{
    int j;
    LNode dummy, *node;
    LinkList prev;

    dummy.next = *L;
    for (j = 0, prev = &dummy;j < i && prev;j++, prev = prev->next)
        ;
    node = malloc(sizeof(LNode));
    node->data = b;
    node->next = prev->next;
    prev->next = node;
    *L = dummy.next;
}

void Purge(LinkList *L)
{
    LNode *newest, *p, *q;
    int is_new;

    newest = *L;
    p = (*L)->next;
    newest->next = NULL;
    while (p) {
        for (is_new = 1, q = *L;q;q = q->next)
            if (q->data == p->data) {
                is_new = 0;
                break;
            }
        q = p->next;
        if (is_new) {
            newest->next = p;
            p->next = NULL;
            newest = p;
        } else {
            free(p);
        }
        p = q;
    }
}

void Inverse(LinkList *L)
{
    LNode dummy, *p, *t;

    dummy.next = NULL;
    for (p = (*L)->next;p;) {
        t = p->next;
        p->next = dummy.next;
        dummy.next = p;
        p = t;
    }

    (*L)->next = dummy.next;
}

void Merge(LinkList la, LinkList lb, LinkList *lc)
{
    LNode *p, *t, dummy;

    t = la->next;
    la->next = NULL;
    la = t;
    t = lb->next;
    lb->next = NULL;
    lb = t;
    for (p = &dummy;la && lb;) {
        t = la->next;
        p->next = la;
        la->next = NULL;
        la = t;
        p = p->next;

        t = lb->next;
        p->next = lb;
        lb->next = NULL;
        lb = t;
        p = p->next;
    }

    for (;la;p = p->next) {
        t = la->next;
        p->next = la;
        la->next = NULL;
        la = t;
    }

    for (;lb;p = p->next) {
        t = lb->next;
        p->next = lb;
        lb->next = NULL;
        lb = t;
    }

    *lc = dummy.next;
}
