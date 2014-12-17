#ifndef FS_H
#define FS_H

#include "config.h"
#include "proc.h"

enum file_type {
    TYPE_FILE = 0x01,
    TYPE_DIR
};

#define PERM_RD 0x01                    // 可读
#define PERM_WR 0x02                    // 可写

#define E_TOO_MANY_FILES    1           // 目录下文件过多
#define E_PERMISSION        2           // 权限不足
#define E_INVALID_TYPE      3           // 文件记录类型错误

// In memory file structure.
struct entry {
    char name[NAME_LENGTH + 1];         // 名称
    enum file_type type;                // 类型
    unsigned int owner_id;              // 所有者 id
    unsigned int owner_perm;            // 所有者权限
    unsigned int other_perm;            // 其他访问者权限

    struct entry *parent;               // 记录所属文件夹
    struct entry *files[MAX_FILES];     // 文件夹下的子文件
    int count;                          // 文件夹下文件数量
    char *content;                      // 文件内容
    
    // TODO file size & create / update date?
};

// 销毁一个文件记录
//
// @param 文件记录
void entry_destroy(struct entry *);

// 创建一个文件
//
// @param 文件名称
// @param 所有者
// @param 所有者权限
// @param 访问者权限
struct entry *entry_create_file(const char *, struct user *, unsigned int, unsigned int);

// 创建一个文件夹
//
// @param 文件夹名称
// @param 所有者
// @param 所有者权限
// @param 访问者权限
struct entry *entry_create_dir(const char *, struct user *, unsigned int, unsigned int);

// 文件记录里面是否包含另外一个文件记录？
//
// @param 文件记录
// @param 子文件记录
int entry_is_dir_contains(const struct entry *, const struct entry *b);

// 添加一个记录到文件夹中
//
// 当文件夹已满的时候返回 -E_TOO_MANY_FILES
//
// @param 文件夹
// @param 记录
int entry_add_to_dir(struct entry *, struct entry *);

// 将一个记录从文件夹中移除
//
// 如果文件不存在文件夹中，不执行移除操作
//
// @param 文件夹
// @param 记录
int entry_remove_from_dir(struct entry *, struct entry *);

// 删除一个记录
//
// 如果该记录为文件夹，则将其所有文件一并删除
//
// @param 记录
int entry_remove(struct entry *);

// 向文件写入内容
//
// 返回写入内容长度
//
// @param 记录
// @param 写入内容
int entry_write_file(struct entry *, const char *);

// 从文件读取内容
//
// 返回读出内容长度
//
// @param 记录
// @param 读出内容指针
int entry_read_file(struct entry *, char *);

#endif /* #ifndef FS_H */
