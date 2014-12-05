#ifndef TICK_H
#define TICK_H

#include "structure.h"

// 进行作业调度系统
//
// @param 资源配额设置
// @param 待运行的作业链表指针
// @param 调度算法实现
int tick(const struct resource *, struct job **, scheduler_fn *);

#endif  /* #ifndef TICK_H */
