#ifndef LIST_H
#define LIST_H

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef char elem_type;

enum status {
    LIST_OK,
    LIST_FAIL
};

/*
 * A simple 1 index base list
 */
struct list {
    elem_type *elem;
    int length;         /* used unit */
    int listsize;       /* list capacity */
};

enum status list_init(struct list **);
void list_destroy(struct list *);
int list_length(struct list *);
enum status list_insert(struct list *, int, elem_type);
enum status list_delete(struct list *, int, elem_type *);
enum status list_get(struct list *, int, elem_type *);
int list_locate(struct list *, elem_type, enum status (*)(elem_type, elem_type));


#endif
