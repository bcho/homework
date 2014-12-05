#include "tick.h"
#include "job.h"
#include "utils.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 将作业链分离成：
//
// - 可以进行调度
// - 未到调度就绪时间
// - 已经完成
//
// 三组
//
// @param 当前系统时间
// @param 系统资源状态
// @param 上一轮的可以执行调度的作业链
// @param 上一轮的未就绪作业链
// @param 上一轮已完成作业链
static void
split(const int tick,
      const struct resource *res,
      struct job *ahead,
      struct job *phead,
      struct job *fhead)
{
    struct job *j, *next;

    next = NULL;

    for (j = ahead->next; j != NULL; j = next) {
        next = j->next;

        // 作业已经完成
        if (j->status == FINISHED) {
            llist_pop(j);
            llist_insert_after(fhead, j);
        // 作业尚未就绪
        } else if (!job_is_runnable(tick, res, j)) {
            llist_pop(j);
            llist_insert_after(phead, j);
        }
    }

    for (j = phead->next; j != NULL; j = next) {
        next = j->next;

        // 作业已经完成
        if (j->status == FINISHED) {
            llist_pop(j);
            llist_insert_after(fhead, j);
        // 作业已经就绪
        } else if (job_is_runnable(tick, res, j)) {
            llist_pop(j);
            llist_insert_after(ahead, j);
        }
    }

    for (j = fhead->next; j != NULL; j = next) {
        next = j->next;

        if (j->status != FINISHED) {
            llist_pop(j);

            // 作业已经就绪
            if (job_is_runnable(tick, res, j))
                llist_insert_after(ahead, j);
            // 作业尚未就绪
            else
                llist_insert_after(phead, j);
        }
    }
}

int
tick(const struct resource *res, struct job **jobs, scheduler_fn scheduler)
{
    int now;                                        // 系统当前时间
    int ran;                                        // 作业运行时间
    struct job available, pending, finished;        // 系统作业链
    struct job *just_ran;

    now = 0;
    available.next = *jobs; available.prev = NULL;
    (*jobs)->prev = &available;
    pending.next = NULL; pending.prev = NULL;
    finished.next = NULL; finished.prev = NULL;
    do {
        split(now, res, &available, &pending, &finished);

        if (available.next) {                               // 进入调度
            // TODO mark resource as using
            ran = scheduler(&available.next, &just_ran);
            now = now + ran;

            // 更新刚刚运行作业的完成时间
            if (just_ran->status == FINISHED)
                just_ran->ftime = now;
        } else {                                        // 空闲状态
            printf("系统空闲中\n");
            usleep(TICK_MS);
            now = now + 1;
        }
    } while (available.next != NULL || pending.next != NULL);

    *jobs = finished.next;
    return now;
}
