#include <stdlib.h>

#include "singly-linked-list.h"

struct list_head *list_create()
{
    struct list_head *new;

    new = malloc(sizeof(struct list_head));
    if (new == NULL) {
        return NULL;
    }

    list_init(new);

    return new;
}

struct list_item *list_item_create(void *data)
{
    struct list_item *new;

    new = malloc(sizeof(struct list_item));
    if (new == NULL) {
        return NULL;
    }

    list_item_init(new, data);

    return new;
}

void list_init(struct list_head *head)
{
    head->first = NULL;
}

void list_item_init(struct list_item *item, void *data)
{
    item->next = NULL;
    item->data = data;
}

void list_destory(struct list_head **phead)
{
    struct list_item *pos;
    struct list_head *head;

    head = *phead;
    list_for_each(pos, head) {
        list_item_destory(&pos);
    }

    free(head);
    *phead = NULL;
}

void list_item_destory(struct list_item **pitem)
{
    free(*pitem);
    *pitem = NULL;
}

int list_empty(struct list_head *head)
{
    return head->first == LIST_END;
}

int list_length(struct list_head *head)
{
    struct list_item *pos;
    int count;

    count = 0;
    list_for_each(pos, head)
        count = count + 1;

    return count;
}

void list_get_ith(struct list_head *head, int i, void **ele)
{
    if (i < 0)
        return;

    struct list_item *p;

    for (p = head->first, i--; p && i > 0; p = p->next, i--)
        ;

    if (i != 0)
        return;
    *ele = p->data;
}

void list_insert(struct list_item *item, struct list_item *new)
{
    if (item == NULL || new == NULL)
        return;

    new->next = item->next;
    item->next = new;
}

void list_insert_before(struct list_head *head,
                        struct list_item *item,
                        struct list_item *new)
{
    if (new == NULL)
        return;

    struct list_item *pos;
    struct list_item sential;

    for (sential.next = head->first, pos = &sential;
         pos != NULL && pos->next != item;
         pos = pos->next)
        ;

    if (pos == NULL)
        return;
    new->next = pos->next;
    pos->next = new;
    head->first = sential.next;
}

void list_del(struct list_head *head, struct list_item *item)
{
    if (item == NULL)
        return;

    struct list_item *pos;

    list_for_each(pos, head)
        if (pos->next == item)
            break;

    if (pos == NULL)
        return;
    pos->next = item->next;
}
