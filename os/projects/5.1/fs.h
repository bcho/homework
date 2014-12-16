#ifndef FS_H
#define FS_H

#include "config.h"

// 文件系统分区数据布局：
//
// +-------------------------------------------------------+  第 0 块
// |                    super-block                        |
// +-------------------------------------------------------+  第 1 块
// |                data block bits mask                   |
// +-------------------------------------------------------+  第 2 块
// |                  IPB 个 inode 记录                    |
// +-------------------------------------------------------+  3 ~ N 块
// |                                                       |
// |                    data blocks                        |
// |                                                       |
// +-------------------------------------------------------+

#define ROOT_INO 1          // 根目录 inode 编号

#define TYPE_FREE 0x0       // 未使用的 inode
#define TYPE_DIR  0x1       // inode 文件夹类型
#define TYPE_FILE 0x2       // inode 文件类型

#define IPB (BLOCK_SIZE / sizeof(struct inode))
#define BPB (BLOCK_SIZE * sizeof(unsigned int))


struct super_block {
    unsigned int size;                          // 分区大小
};

struct inode {
    short type;                                 // inode 类型
    unsigned int size;                          // 文件大小字节数
    unsigned int addrs[NO_BLOCK];               // 文件块地址
};

// 文件夹条目记录
struct dir_entry {
    unsigned int owner_perm;                    // 文件拥有者权限 bits mask
    unsigned int other_perm;                    // 其他人的权限 bits mask
    unsigned short inum;                        // inode 编号
    char name[NAME_SIZE];                       // 条目名称
};

// (内存中) 文件记录定义
struct file {
    unsigned int owner_perm;                    // 文件拥有者权限 bits mask
    unsigned int other_perm;                    // 其他人的权限 bits mask
    struct inode *ip;                           // 对应 index node 关联
    unsigned int off;                           // 文件当前内容起始偏移
};

// 初始化分区
void fs_init();

// 分配一个 inode
//
// @param inode 类型
struct inode *inode_alloc(short);

#endif /* #ifndef FS_H */
