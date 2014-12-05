#include "sched.h"
#include "job.h"

static int
compare_by_rtime(const struct job a, const struct job b)
{
    return (a.rtime - b.rtime);
}

int
sjf_scheduler(struct job *rhead, struct job **ran)
{
    struct job *j;

    if (!rhead || !rhead->next)
        return 0;

    // 根据运行时间进行排序
    job_sort(&rhead->next, compare_by_rtime);
    j = rhead->next;

    j->status = RUNNING;
    job_run(j);

    *ran = j;
    return j->rtime;
}
