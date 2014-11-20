#include "proc.h"

#include <stdlib.h>
#include <stdio.h>

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
