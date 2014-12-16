#include "mem_dev.h"
#include "fs.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

// 在内存中的分区数据
char *storage;

void
mem_dev_init(unsigned int size)
{
    struct super_block sb;

    // 确保分区大小至少有一个块
    size = MAX(size, BLOCK_SIZE);

    // TODO clean up storage after using it
    storage = malloc(size);
    if (storage == NULL)
        goto failed;
    bzero(storage, size);

    // 写入 super block 信息
    sb.size = size;
    mem_dev_write((unsigned char *) &sb, 0);

    return;

failed:
    PANIC("内存分区初始化失败");
}

unsigned char *
mem_dev_read(unsigned int bnum)
{
    unsigned char *buf;
    char *begin;

    buf = malloc(sizeof(unsigned char *) * BLOCK_SIZE);
    if (buf == NULL)
        PANIC("读取内存分区失败");

    begin = (char *) storage + bnum * BLOCK_SIZE;
    memmove(buf, begin, BLOCK_SIZE);

    return buf;
}

void
mem_dev_write(unsigned char *buf, unsigned int bnum)
{
    char *begin;

    begin = (char *) storage + bnum * BLOCK_SIZE;
    memmove(begin, buf, BLOCK_SIZE);
}

void
mem_dev_free(unsigned char *buf)
{
    free(buf);
}
