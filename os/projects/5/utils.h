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


// windows 下的 getline 实现
//
// @see getline(3)
size_t u_getline(char **, size_t *, FILE *);

#endif  /* #ifndef UTILS_H */
