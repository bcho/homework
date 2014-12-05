#include "sched.h"
#include "job.h"

int
fcfs_scheduler(struct job **runnable, struct job **ran)
{
    struct job *j;

    if (!*runnable)
        return 0;

    // TODO sort by arrival time.
    j = *runnable;

    j->status = RUNNING;
    job_run(j);

    *ran = j;
    return j->rtime;
}
