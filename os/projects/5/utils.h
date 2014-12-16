#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 停止程序运行
//
// @param 异常原因
#define PANIC(n) \
    do { \
        printf("%s\n", (n)); \
        exit(-1); \
    } while (0)


#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif  /* #ifndef UTILS_H */
