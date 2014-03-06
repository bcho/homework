#include <stdlib.h>

#include "list.h"

enum status list_init(struct list **p)
{
    struct list *l;

    l = malloc(sizeof(struct list));
    if (l == NULL) {
        return LIST_FAIL;
    }
    l->elem = malloc(sizeof(elem_type) * LIST_INIT_SIZE);
    if (l->elem == NULL) {
        return LIST_FAIL;
    }

    l->length = 0;
    l->listsize = LIST_INIT_SIZE;

    *p = l;
    return LIST_OK;
}

void list_destroy(struct list *l)
{
    free(l->elem);
    free(l);
}

int list_length(struct list *l)
{
    if (l != NULL)
        return l->length;
    return 0;
}

enum status list_insert(struct list *l, int index, elem_type e)
{
    if (l == NULL)
        return LIST_FAIL;
    if (index < 1 || index > l->length + 1)
        return LIST_FAIL;

    int i;

    /* Request more rooms. */
    if (l->length >= l->listsize) {
        l->elem = realloc(l->elem, (l->listsize + LISTINCREMENT) * sizeof(elem_type));
        if (l->elem == NULL) {
            return LIST_FAIL;
        }
        l->listsize = l->listsize + LISTINCREMENT;
    }

    for (i = l->length; i >= index; i--)
        *(l->elem + i) = *(l->elem + i - 1);
    *(l->elem + index - 1) = e;
    l->length = l->length + 1;

    return LIST_OK;
}

enum status list_delete(struct list *l, int index, elem_type *e)
{
    if (l == NULL)
        return LIST_FAIL;
    if (index < 1 || index > l->length)
        return LIST_FAIL;

    int i;

    if (list_get(l, index, e) != LIST_OK)
        return LIST_FAIL;
    for (i = index; i <= l->length; i++)
        *(l->elem + i - 1) = *(l->elem + i);

    return LIST_OK;
}

enum status list_get(struct list *l, int index, elem_type *e)
{
    if (l == NULL)
        return LIST_FAIL;
    if (index < 1 || index > l->length)
        return LIST_FAIL;

    *e = *(l->elem + index - 1);
    return LIST_OK;
}

int list_locate(struct list *l, elem_type e, enum status (*compare)(elem_type, elem_type))
{
    int i;
    elem_type p;

    for (i = 1; i <= l->length; i++) {
        if (list_get(l, i, &p) != LIST_OK)
            return LIST_FAIL;
        if (compare(p, e) == LIST_OK)
            return i;
    }

    return -1;
}
