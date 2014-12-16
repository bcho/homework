#include "fs.h"
#include "mem_dev.h"

#include <string.h>

// superblock 记录
struct super_block *sb;

// data node bits mask 记录
unsigned char *dnode_map;

void
fs_init()
{
    // TODO clean up after using it.
    sb = (struct super_block *) mem_dev_read(0);
    dnode_map = mem_dev_read(1);
}

struct inode *
inode_alloc(short type)
{
    struct inode *ip;
    unsigned int inum;
    unsigned char *inode_buf;

    // Just assume we have only 1 block for inodes.
    inode_buf = mem_dev_read(2);

    ip = NULL;
    for (inum = 0; inum < IPB; inum++) {
        ip = (struct inode *) inode_buf + sizeof(struct inode) * inum;
        if (ip->type == TYPE_FREE) {
            memset(ip, 0, sizeof(struct inode));
            ip->type = type;

            // 写入到磁盘记录中
            mem_dev_write(inode_buf, 2);
            break;
        }
    }

done:
    mem_dev_free(inode_buf);

    return ip;
}
