#ifndef IO_H
#define IO_H

#include "config.h"

// 缓冲块定义
struct buf {
    unsigned char data[BLOCK_SIZE];
};

#endif /* #ifndef IO_H */
