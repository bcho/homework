#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>

// 系统调用 malloc 接口定义
// 
// @param 分配内存大小
// @see malloc(3)
void *my_malloc(size_t);

// 系统调用 free 接口定义
//
// @param 被回收的内存块
// @see malloc(3)
void my_free(void *);

// 显示内存使用状态
void my_display();


#define BLOCK_TMPL "" \
    "+----------------------------------+\n" \
    "| 起始地址: 0x%llx                  \n" \
    "| 内存大小: %d bytes                \n" \
    "| 是否被使用: %d                    \n" \
    "+----------------------------------+\n"


#endif  /* #ifndef MALLOC_H */
