#include "resource.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

struct resource *
resource_create(const char *name, int quota)
{
    struct resource *r;

    r = malloc(sizeof(struct resource));
    if (r == NULL)
        goto fail;
    strncpy(r->name, name, NAME_LENGTH - 1);
    r->name[NAME_LENGTH - 1] = 0;
    r->quota = quota;
    r->next = NULL;
    r->prev = NULL;

    return r;

fail:
    PANIC("创建资源描述失败");
}

void
resource_destroy(struct resource *r)
{
    struct resource *head, *next;

    for (head = r; r != NULL && r != head; r = next) {
        next = r->next;
        free(r);
        r = next;
    }
}

void
resource_info(const char *fmt, struct resource *r)
{
    printf(fmt, r->name, r->quota);
}

struct resource *
resource_append(struct resource **rlist, const char *name, int quota)
{
    struct resource *r;
    struct resource head;

    head.next = *rlist;

    // 找到同名资源，更新配额
    if ((r = resource_get_by_name(*rlist, name)) != NULL) {
        r->quota = quota;
        return r;
    }

    // 没有同名资源，新建一个记录
    r = resource_create(name, quota);
    llist_insert_after(&head, r);
    *rlist = head.next;

    return r;
}

struct resource *
resource_get_by_name(const struct resource *rlist, const char *name)
{
    struct resource *r;

    llist_for_each(r, (struct resource *) rlist)
        if (strcmp(name, r->name) == 0)
            return r;
    return NULL;
}

int
resource_get_quota(const struct resource *rlist, const char *name)
{
    struct resource *r;

    if ((r = resource_get_by_name(rlist, name)) != NULL)
        return r->quota;

    return 0;
}

int
resource_check_quota(const struct resource *rlist, const char *name, int quota)
{
    struct resource *r;

    r = resource_get_by_name(rlist, name);
    if (r == NULL || r->quota < quota)
        return 0;

    return 1;
}
