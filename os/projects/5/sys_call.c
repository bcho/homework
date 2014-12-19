#include "sys_call.h"
#include "fs.h"
#include "proc.h"
#include "utils.h"
#include "config.h"

#include <string.h>
#include <stdio.h>

// 文件描述符
int fd_opened;
struct entry *fds[MAX_FD + 1]; // fd starts from 1

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
    memset(fds, 0, sizeof(fds));
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
open(const struct user *user, const char *path, unsigned int needed_perm)
{
    int i;
    struct entry *file;
    unsigned int perm_mask;

    // 只支持绝对路径
    if (! IS_ABSOLUTE_PATH(path))
        return - E_FAIL;

    file = entry_find(root, path);

    // 文件不存在或者类型不为文件
    if (file == NULL || file->type != TYPE_FILE)
        return - E_INVALID_TYPE;

    if (file->owner_id == user_get_id(user))
        perm_mask = file->owner_perm;
    else
        perm_mask = file->other_perm;
    // 权限不足
    if (perm_mask & needed_perm == 0)
        return - E_PERMISSION;

    // 打开文件太多
    if (fd_opened > MAX_FD)
        return - E_TOO_MANY_FILES;

    for (i = 1; i <= MAX_FD; i++)
        // FIXME fd reuse without permission.
        if (fds[i] == NULL) {
            fds[i] = file;
            fd_opened = fd_opened + 1;

            return i;
        }

    return - E_FAIL;
}

int
close(int fd)
{
    fds[fd] = NULL;
    fd_opened = MAX(fd_opened - 1, 0);

    return E_OK;
}

int
read(int fd, char *buf)
{
    struct entry *file;

    file = fds[fd];
    if (!file)
        return - E_FAIL;

    return entry_read_file(file, buf);
}

int
write(int fd, const char *buf)
{
    struct entry *file;

    file = fds[fd];
    if (!file)
        return - E_FAIL;

    return entry_write_file(file, buf);
}

int
delete(const struct user *user, const char *path)
{
    struct entry *e;

    // 只支持绝对路径
    if (! IS_ABSOLUTE_PATH(path))
        return - E_FAIL;

    e = entry_find(root, path);

    // 指定目标不存在
    if (e == NULL)
        return - E_FAIL;

    // 只有记录所有者可以删除
    if (e->owner_id != user_get_id(user))
        return - E_PERMISSION;

    return entry_remove(e);
}

int
create(const struct user *user,
       enum file_type type,
       const char *path,
       unsigned int owner_perm,
       unsigned int other_perm)
{
    int path_length = strlen(path);
    unsigned int perm_mask;
    char parent_path[path_length];
    const char *c;
    char *d, *fname;
    struct entry *parent, *e; 
    
    // 只支持绝对路径
    if (! IS_ABSOLUTE_PATH(path))
        return - E_FAIL;

    // TODO refactor path string
    fname = rindex(path, PATH_SEP);
    // 名称错误
    if (fname == NULL)
        return - E_FAIL;
    else
        fname = fname + 1;

    for (c = path, d = parent_path; *c != 0 && c != fname;)
        *d++ = *c++;
    if (strlen(parent_path) > 1)
        *(d - 1) = 0;

    parent = entry_find(root, parent_path);
    // 父文件夹不存在
    if (parent == NULL || parent->type != TYPE_DIR)
        return - E_FAIL;

    if (parent->owner_id == user_get_id(user))
        perm_mask = parent->owner_perm;
    else
        perm_mask = parent->other_perm;
    // 权限不足
    if (perm_mask & PERM_WR == 0)
        return - E_PERMISSION;
    // 已经包含该文件
    if (entry_is_dir_contains(parent, fname))
        return - E_FAIL;

    e = entry_create(fname, type, user, owner_perm, other_perm);
    return entry_add_to_dir(parent, e);
}

int
mv(const struct user *user, const char *src_path, const char *dest_path)
{
    unsigned int perm_mask;
    struct entry *src, *dest;

    // 只支持绝对路径
    if (! IS_ABSOLUTE_PATH(src_path) || ! IS_ABSOLUTE_PATH(dest_path))
        return - E_FAIL;

    // 指定路径不存在
    src = entry_find(root, src_path);
    if (src == NULL)
        return - E_FAIL;
    dest = entry_find(root, dest_path);
    if (dest == NULL || dest->type != TYPE_DIR)
        return - E_FAIL;
    
    // 只有文件所有者可以移动文件夹
    if (src->owner_id != user_get_id(user))
        return - E_PERMISSION;

    if (dest->owner_id == user_get_id(user))
        perm_mask = dest->owner_perm;
    else
        perm_mask = dest->other_perm;
    // 不能写入到目标文件夹
    if (perm_mask & PERM_WR == 0)
        return - E_PERMISSION;

    return entry_add_to_dir(dest, src);
}

static void
perm_stat(unsigned int perm_mask)
{
    if (perm_mask & PERM_RD)
        printf("r");
    else
        printf("-");
    if (perm_mask & PERM_WR)
        printf("w");
    else
        printf("-");
    if (perm_mask & PERM_EX)
        printf("x");
    else
        printf("-");
}

int
stat(const struct user *user, const char *path)
{
    struct entry *e;
    struct user owner;

    // 只支持绝对路径
    if (! IS_ABSOLUTE_PATH(path))
        return - E_FAIL;

    e = entry_find(root, path);
    // 指定路径不存在
    if (e == NULL)
        return - E_FAIL;
    
    // 没有权限查看
    if (e->owner_id != user_get_id(user) && (e->other_perm & PERM_RD == 0))
        return - E_PERMISSION;

    // 权限组
    switch (e->type) {
        case TYPE_DIR:
            printf("d");
            break;
        default:
            printf("-");
    }
    perm_stat(e->owner_perm);
    perm_stat(e->other_perm);

    // 所有者
    if (user_get_by_id(e->owner_id, &owner) != E_OK)
        printf(" unknown");
    else
        printf(" %s", owner.name);

    // 文件名
    printf(" %s\n", e->name);

    return E_OK;
}
