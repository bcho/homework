#include "link_list.h"

#include <stdio.h>

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
