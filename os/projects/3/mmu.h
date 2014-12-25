#ifndef MMU_H
#define MMU_H

#include "config.h"

// 虚拟内存地址格式
//
// +-------6-----+----------10---------+
// | page index  | offset within page  |
// +-------------+---------------------+

// 物理内存地址格式
//
// +-----5-----+--------10----------+
// |frame index| offset within page |
// +-----------+--------------------+

// 计算虚拟地址页数
#define PTX(va) (((unsigned int)(va) >> PTXSHIFT) & 0x3F)

// 计算虚拟地址中的偏移
#define VAO(va) (((unsigned int)(va)) & 0x3FF)

// 生成物理地址
//
// @param 物理页号
// @param 偏移
#define PPA(p, o) (((p) << FRXSHIFT) | (o))

#endif /* #ifndef MMU_H */
