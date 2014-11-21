#ifndef SCHED_H
#define SCHED_H

#include "proc.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

// 进程调度接口
//
// 所有进程结束后返回运行总时间片
//
// @param 进程列表
int schedule(struct proc *);

// 程序异常
// 
// @param 异常原因
#define PANIC(n) \
    do { \
        printf("%s\n", (n)); \
        exit(-1); \
    } while (0)

// 从命令行输入获取
//
// - 进程数
// - 进程时间片分配算法
// - 进程优先度分配算法
//
// @param 命令行输入长度
// @param 命令行输入
// @param 进程数
// @param 时间片分配算法
// @param 优先度分配算法
#define PARSE_CLI(argc, argv, count, ntime, priority) \
    do { \
        if ((argc) <= 1) \
            PANIC("请输入调度进程数"); \
        count = atoi((argv)[1]); \
        ntime = MEAN; \
        priority = MEAN; \
        if ((argc) >= 3) \
            ntime = dist_algo_parse((argv)[2]); \
        if ((argc) >= 4) \
            priority = dist_algo_parse((argv)[3]); \
    } while (0)


// 准备进程链表
//
// @param 进程链表头
// @param 进程总数
// @param 时间片分配算法
// @param 优先度分配算法
#define PREPARE_PROCS(procs, count, ntime, priority) \
    do { \
        procs = proc_create_list((count)); \
        if (procs == NULL) \
            PANIC("创建进程失败"); \
        proc_fill_ntime((ntime), (count), procs); \
        proc_fill_priority((priority), (count), procs); \
    } while (0)

#endif /* #ifndef SCHED_H */
