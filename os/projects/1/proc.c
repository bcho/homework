#include "proc.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


// 每个时间片长度为 100 毫秒
// TODO windows compatible
#define TIME_SLICE_MICROSECOND 100000

// 每次程序运行使用的时间片数量
#define RUN_SLICES 1


struct proc *
proc_create(int pid, int priority, int ntime)
{
    struct proc *p;

    p = malloc(sizeof(struct proc));
    if (p == NULL)
        goto finish;

    p->pid = pid;
    p->state = WAITING;
    sprintf(p->name, "%d", p->pid);         // 使用 pid 作为进程名称
    p->priority = priority;
    p->ntime = ntime;
    p->rtime = 0;
    p->pprev = NULL;
    p->next = NULL;

finish:
    return p;
}

void
proc_destory(struct proc *p)
{
    if (p == NULL)
        return;

    free(p);
}

void
proc_info(struct proc p)
{
    char *state;

    switch (p.state) {
        case WAITING: state = "等待中"; break;
        case RUNNING: state = "运行中"; break;
        case FINISHED: state = "已结束"; break;
        default: state = "未知状态";
    }

    printf("进程: %s\n", p.name);
    printf("\t进程状态：%s\t进程优先度：%d\n", state, p.priority);
    printf("\t进程需要运行时间片：%d\t已运行时间片：%d\n", p.ntime, p.rtime);
    printf("\n");
}

int
proc_run(struct proc *p)
{
    int ran_slices;

    if (p->state != RUNNING)
        return - E_UNRUNABLE;

    ran_slices = 0;
    if (p->rtime < p->ntime) {
        // TODO windows compatible
        usleep(RUN_SLICES * TIME_SLICE_MICROSECOND);

        p->rtime = p->rtime + RUN_SLICES;
        ran_slices = RUN_SLICES;
    }

    if (p->rtime >= p->ntime)           // 进程已经完成运行
        p->state = FINISHED;

    return ran_slices;
}
