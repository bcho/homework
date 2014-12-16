#include "config.h"
#include "fs.h"
#include "proc.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

// 创建一个文件记录
static struct entry *
entry_create(const char *name,
             enum file_type type,
             struct user *owner,
             unsigned int owner_perm,
             unsigned int other_perm)
{
    struct entry *e = NULL;

    e = malloc(sizeof(struct entry));
    if (e == NULL)
        goto failed;
    memset(e, 0, sizeof(struct entry));
    strncpy(e->name, name, NAME_LENGTH);
    e->owner_id = user_get_id(owner);
    e->type = type;
    e->owner_perm = owner_perm;
    e->other_perm = other_perm;

    return e;

failed:
    if (e != NULL)
        free(e);

    PANIC("创建文件记录失败");
}

void
entry_destroy(struct entry *e)
{
    if (e->type == TYPE_FILE && e->content != NULL)
        free(e->content);
    free(e);
}

struct entry *
entry_create_file(const char *name,
                  struct user *owner,
                  unsigned int owner_perm,
                  unsigned int other_perm)
{
    return entry_create(name, TYPE_FILE, owner, owner_perm, other_perm);
}

struct entry *
entry_create_dir(const char *name,
                 struct user *owner,
                 unsigned int owner_perm,
                 unsigned int other_perm)
{
    return entry_create(name, TYPE_DIR, owner, owner_perm, other_perm);
}

int
entry_is_dir_contains(const struct entry *a, const struct entry *b)
{
    int i;

    if (a->type == TYPE_FILE)
        return a == b;

    if (a == b)
        return 1;

    for (i = 0; i < a->count; a++)
        if (entry_is_dir_contains(a->files[i], b))
            return 1;

    return 0;
}

int
entry_add_to_dir(struct entry *dir, struct entry *e)
{
    if (dir->type != TYPE_DIR)
        return - E_INVALID_TYPE;

    if (dir->count + 1 > MAX_FILES)
        return - E_TOO_MANY_FILES;

    // 不能使用子文件夹包含父文件夹
    if (entry_is_dir_contains(e, dir))
        return - E_INVALID_TYPE;

    entry_remove_from_dir(e->parent, e);
    dir->files[dir->count] = (struct entry *) e;
    dir->count = dir->count + 1;
    e->parent = dir;

    return 0;
}

int
entry_remove_from_dir(struct entry *dir, struct entry *e)
{
    int i;

    if (! dir || dir->type != TYPE_DIR)
        return 0;

    for (i = 0; i < dir->count - 1; i++)
        if (dir->files[i] == e)
            break;
    dir->files[i] = dir->files[dir->count - 1];
    dir->count = dir->count - 1;
    e->parent = NULL;

    return 0;
}

int
entry_remove(struct entry *e)
{
    int i, rv;

    if (! e)
        return 0;

    // 先删除子文件
    if (e->type == TYPE_DIR)
        for (i = 0; i < e->count; i++)
            if ((rv = entry_remove(e->files[i])) != 0)
                return rv;

    // 移除到父结点的关联
    entry_remove_from_dir(e->parent, e);
    entry_destroy(e);

    return 0;
}

int
entry_write_file(struct entry *file, const char *content)
{
    int content_length;

    if (file->type != TYPE_FILE)
        return - E_INVALID_TYPE;

    if (file->content != NULL)
        free(file->content);

    content_length = strlen(content);
    file->content = malloc(sizeof(char) * (content_length + 1));
    if (file->content == NULL)
        PANIC("分配文件空间失败");
    memset(file->content, 0, sizeof(char) * (content_length + 1));
    strncpy(file->content, content, content_length);

    return content_length;
}

int
entry_read_file(struct entry *file, char **dest)
{
    int content_length;

    if (file->type != TYPE_FILE)
        return - E_INVALID_TYPE;

    if (file->content == NULL)
        return 0;

    content_length = strlen(file->content);
    strncpy(*dest, file->content, content_length);
    dest[content_length] = 0;

    return content_length;
}
