#include "sched.h"
#include "job.h"

static int
compare_by_atime(const struct job a, const struct job b)
{
    return (a.atime - b.atime);
}

int
fcfs_scheduler(struct job **runnable, struct job **ran)
{
    struct job *j;

    if (!*runnable)
        return 0;

    // 根据到达时间进行排序
    job_sort(runnable, compare_by_atime);
    j = *runnable;

    j->status = RUNNING;
    job_run(j);

    *ran = j;
    return j->rtime;
}
