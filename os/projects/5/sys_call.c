#include "sys_call.h"
#include "fs.h"
#include "proc.h"
#include "utils.h"
#include "config.h"

#include <string.h>

// 文件描述符
int fd_opened;
struct entry *fd[MAX_FD + 1]; // fd starts from 1

// 根目录
struct entry *root;

// 用户记录
int user_created;
struct user *users[MAX_USER];

int
init()
{
    struct user root_user;

    memset(users, 0, sizeof(users));
    user_created = 0;
    memset(fd, 0, sizeof(fd));
    fd_opened = 0;

    // 创建根用户
    if (user_get_by_id(useradd("root"), &root_user) != E_OK)
        PANIC("系统初始化失败");

    // 创建根目录
    root = entry_create_dir("/",
                            &root_user,
                            PERM_WR | PERM_RD,
                            PERM_WR | PERM_RD);

    return E_OK;
}

int
cleanup()
{
    // TODO
    return E_OK;
}

int
useradd(const char *name)
{
    if (user_created >= MAX_USER)
        return - E_TOO_MANY_USERS;

    // uid starts from 1
    users[user_created] = user_create(user_created + 1, name);
    user_created = user_created + 1;

    return user_created;
}

int
user_get_by_id(int id, struct user *dest)
{
    int i, found;
    struct user *src;

    for (i = 0, found = 0; i < MAX_USER; i++) {
        if (users[i] == NULL)
            continue;
        src = users[i];
        if (user_get_id(src) == id) {
            memcpy(dest, src, sizeof(struct user));
            found = 1;
            break;
        }
    }

    return found ? E_OK : - E_FAIL;
}

#define IS_ABSOLUTE_PATH(x) (strlen((x)) > 0 && (x)[0] == '/')

int
open(const struct user *user, const char *path)
{
    struct entry *file;

    // 只支持绝对路径
    if (! IS_ABSOLUTE_PATH(path))
        return - E_FAIL;

    return 0;
}
