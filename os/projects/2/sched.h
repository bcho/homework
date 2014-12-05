#ifndef SCHED_H
#define SCHED_H

#include "structure.h"

// 先来先服务
//
// @see scheduler_fn
int fcfs_scheduler(struct job *, struct job **);

// 最短作业优先
//
// @see scheduler_fn
int sjf_scheduler(struct job *, struct job **);

// 响应比优先
//
// @see scheduler_fn
int hrn_scheduler(struct job *, struct job **);

#endif  /* #ifndef SCHED_H */
