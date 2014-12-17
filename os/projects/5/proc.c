#include "proc.h"
#include "utils.h"
#include "config.h"

#include <stdlib.h>
#include <string.h>


struct user *
user_create(int id, const char *name)
{
    struct user *u = NULL;

    u = malloc(sizeof(struct user));
    if (u == NULL)
        PANIC("创建用户失败");
    memset(u, 0, sizeof(struct user));
    u->id = id;
    strncpy(u->name, name, MIN(strlen(name), NAME_LENGTH));

    return u;
}

void
user_destory(struct user *u)
{
    free(u);
}


int
user_get_id(struct user *user)
{
    return user->id;
}
