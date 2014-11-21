#include "proc.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


// 每个时间片长度为 100 毫秒
// TODO windows compatible
#define TIME_SLICE_MICROSECOND 100000

// 每次程序运行使用的时间片数量
#define RUN_SLICES 1


struct proc *
proc_create(int pid, double priority, int ntime)
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

struct proc *
proc_create_list(int count)
{
    struct proc head;
    struct proc *p;

    head.next = NULL;
    for (; count > 0; count--) {
        p = proc_create(count, 0, 0);
        if (p == NULL)
            goto fail;
        proc_insert(&head, p);
    }
    return head.next;

fail:
    return NULL;
}

void
proc_destory_list(struct proc *head)
{
    struct proc *proc;

    for (proc = head; proc != NULL;) {
        head = proc->next;
        proc_destory(proc);
        proc = head;
    }
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
    printf("\t进程状态：%s\t进程优先度：%.3f\n", state, p.priority);
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

// 使用特定分布算法生成一个序列
//
// @param 分布算法
// @param 序列长度
static double *
fill_seq_with(enum dist_algo algo, int count)
{
    double *seq;
    void (*seq_maker)(int, double *);

    if (count <= 0)
        goto fail;

    seq = malloc(sizeof(double) * count);
    if (seq == NULL)
        goto fail;

    switch (algo) {
        case MEAN: seq_maker = make_mean_seq; break;
        case INCR: seq_maker = make_increment_seq; break;
        case NORM: seq_maker = make_normal_distribution_seq; break;
        default: goto fail;
    }

    srand(time(NULL));
    seq_maker(count, seq);
    return seq;

fail:
    return NULL;
}

void
proc_fill_priority(enum dist_algo algo, int count, struct proc *procs)
{
    int i;
    double *seq = NULL;
    struct proc *p;

    seq = fill_seq_with(algo, count);
    if (seq == NULL)
        goto finish;

    i = 0;
    proc_for_each(p, procs) {
        p->priority = seq[i];
        i = i + 1;
    }

finish:
    if (seq != NULL)
        free(seq);
    return;
}

void
proc_fill_ntime(enum dist_algo algo, int count, struct proc *procs)
{
    int i;
    double *seq = NULL;
    struct proc *p;

    seq = fill_seq_with(algo, count);
    if (seq == NULL)
        goto finish;

    i = 0; proc_for_each(p, procs)
    {
        p->ntime = (int) ABS(seq[i]);

        i = i + 1;
    }

finish:
    if (seq != NULL)
        free(seq);
    return;
}
