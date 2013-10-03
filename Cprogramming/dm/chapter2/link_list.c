#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"

#include "link_list.h"

#define _SIZE (sizeof(struct LNode))


LinkList create_link_list_from_string(char *str)
{
    char *c;
    LNode *dummy, *prev, *p;

    dummy = NULL;
    prev = NULL;
    for (c = str;*c != '\0';c++) {
        p = malloc(_SIZE);
        assert(p != NULL);
        p->data = *c;
        p->next = NULL;

        if (dummy == NULL)
            dummy = p;
        else
            prev->next = p;
        prev = p;
    }

    return dummy;
}

LinkList create_link_list_from_string_with_dummy(char *str)
{
    LNode *dummy;

    dummy = malloc(_SIZE);
    assert(dummy != NULL);
    dummy->data = 0;
    dummy->next = create_link_list_from_string(str);

    return dummy;
}

void destory_link_list(LinkList list)
{
    LNode *next;

    while (list != NULL) {
        next = list->next;
        free(next);
        list = next;
    }
}

LNode *get_nth_from_link_list(LinkList list, int n)
{
    while (n && list) {
        list = list->next;
        n--;
    }

    return list;
}

char *link_list_to_string(LinkList list)
{
    // quick & dirty
    char buf[1024];
    int i;
    char *str;

    for (i = 0;list;list = list->next)
        if (list->data != 0)
            buf[i++] = list->data;
    buf[i] = 0;

    str = malloc(sizeof(char) * (strlen(buf) + 1));
    strncpy(str, buf, i + 1);
    str[i] = 0;

    return str;
}
