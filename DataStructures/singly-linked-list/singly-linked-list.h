#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

/* 
 * Singly listed list with sentinel head implementation.
 **/

#define LIST_END NULL

struct list_head {
    struct list_item *first;
};

struct list_item {
    struct list_item *next;
    void *data;
};

extern struct list_head *list_create();
extern struct list_item *list_item_create(void *);

extern void list_init(struct list_head *);
extern void list_item_init(struct list_item *, void *);
extern void list_destory(struct list_head **);
extern void list_item_destory(struct list_item **);

extern int list_empty(struct list_head *);
extern int list_length(struct list_head *);

extern void list_get_ith(struct list_head *, int, void *);

extern void list_insert(struct list_item *, struct list_item *);
extern void list_insert_before(struct list_head *,
                               struct list_item *,
                               struct list_item *);

extern void list_del(struct list_head *, struct list_item *);

#define list_for_each(pos, head) \
    for (pos = (head)->first; pos != LIST_END; pos = pos->next)

#endif
