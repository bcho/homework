#include "sched.h"
#include "job.h"

static int
compare_by_atime(const struct job a, const struct job b)
{
    return (a.atime - b.atime);
}

int
fcfs_scheduler(struct job *rhead, struct job **ran)
{
    struct job *j;

    if (!rhead || !rhead->next)
        return 0;

    // 根据到达时间进行排序
    job_sort(&rhead->next, compare_by_atime);
    j = rhead->next;

    j->status = RUNNING;
    job_run(j);

    *ran = j;
    return j->rtime;
}
