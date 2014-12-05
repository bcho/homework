#include "sched.h"
#include "job.h"
#include "utils.h"

#include <stdlib.h>

struct job_responsive_ratio {
    struct job *j;
    double ratio;
};

// 创建作业响应记录数组
//
// @param 当前系统时间
// @param 作业记录链表
// @param 创建数量
static struct job_responsive_ratio *
job_responsive_ratio_create_from_jobs(int tick, struct job *jobs, int count)
{
    int i;
    struct job *j;
    struct job_responsive_ratio *r;

    r = malloc(sizeof(struct job_responsive_ratio) * count);
    if (r == NULL)
        goto fail;

    for (i = 0, j = jobs; i < count; i++, j = j->next) {
        r[i].j = j;
        r[i].ratio = ((tick - j->atime + 1) + j->rtime) / (double) j->rtime;
    }

    if (!(count == i && j == NULL))
        goto fail;

    return r;

fail:
    if (r != NULL)
        free(r);

    PANIC("创建响应记录失败");
}

static int
compare_by_responsive_ratio(const void *a, const void *b)
{
    struct job_responsive_ratio *ra, *rb;

    ra = (struct job_responsive_ratio *) a;
    rb = (struct job_responsive_ratio *) b;
    return (int) rb->ratio - (int) ra->ratio;
}

int
hrn_scheduler(int tick, struct job *rhead, struct job **ran)
{
    int jobs_count;
    struct job *j;
    struct job_responsive_ratio *ratios;

    if (!rhead || !rhead->next)
        return 0;

    jobs_count = 0;
    llist_for_each(j, rhead->next)
        jobs_count = jobs_count + 1;
    j = rhead->next;
    ratios = job_responsive_ratio_create_from_jobs(tick, j, jobs_count);

    // 根据响应比进行排序
    qsort(&ratios[0],
          jobs_count,
          sizeof(struct job_responsive_ratio),
          compare_by_responsive_ratio);

    j = ratios[0].j;
    free(ratios);

    j->status = RUNNING;
    job_run(j);

    *ran = j;
    return j->rtime;
}
