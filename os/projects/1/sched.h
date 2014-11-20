#ifndef SCHED_H
#define SCHED_H

#include "proc.h"

// 进程调度接口
//
// 所有进程结束后返回运行总时间片
//
// @param 进程列表
int schedule(struct proc *);

#endif /* #ifndef SCHED_H */
