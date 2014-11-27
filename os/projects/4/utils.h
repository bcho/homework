#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define E_SBRK ((void *) -1)

// 请求堆进行分配接口
//
// @param 分配内存字节数量
// @see sbrk(2)
void *u_sbrk(intptr_t);


// 内存对齐基准
#define ALIGNMENT (8)

// 地址向上对齐
//
// @param 待对齐地址
#define ALIGN(x) (((x) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))


// 停止程序运行
//
// @param 异常原因
#define PANIC(n) \
    do { \
        printf("%s\n", (n)); \
        exit(-1); \
    } while (0)


#define MAX(a, b) ((a) > (b) ? (a) : (b))

#endif  /* #ifndef UTILS_H */
