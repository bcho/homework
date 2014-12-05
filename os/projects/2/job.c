#include "job.h"
#include "resource.h"
#include "utils.h"
#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct job*
job_create(const char *user,
           const char *name,
           int atime,
           int rtime,
           struct resource *res)
{
    struct job *r;

    r = malloc(sizeof(struct job));
    if (r == NULL)
        goto fail;
    strncpy(r->user, user, NAME_LENGTH - 1);
    r->user[NAME_LENGTH - 1] = 0;
    strncpy(r->name, name, NAME_LENGTH - 1);
    r->name[NAME_LENGTH - 1] = 0;
    r->status = STANDBY;
    r->atime = atime;
    r->ftime = -1;
    r->rtime = rtime;
    r->res = res;
    r->next = NULL;

    return r;

fail:
    PANIC("创建作业失败");
}

void
job_destroy(struct job *j)
{
    struct job *head, *next;

    for (head = j; j != NULL && j != head; j = next) {
        next = j->next;
        resource_destroy(j->res);
        free(j);
        j = next;
    }
}

int
job_run(struct job *j)
{
    if (j->status != RUNNING)
        return 0;

    printf("正在运行作业：%s\n", j->name);
    usleep(TICK_MS * j->rtime);
    j->status = FINISHED;

    return j->rtime;
}

void
job_info(struct job *j)
{
    char *status_str;
    double turnover_time = 0;
    double weighted_turnover_time = 0;
    struct resource *r;

    if (j->status == FINISHED) {
        turnover_time = j->ftime - j->atime + 1;
        weighted_turnover_time = turnover_time / j->rtime;
    }

    switch (j->status) {
        case STANDBY:
            status_str = "就绪";
            break;
        case RUNNING:
            status_str = "运行中";
            break;
        case FINISHED:
            status_str = "已完成";
            break;
        default:
            status_str = "未知";
    }

    printf("作业 %s\t用户 %s\t状态 %s\n", j->name, j->user, status_str);
    printf("到达时间： %d\t运行时间： %d\n", j->atime, j->rtime);
    if (j->status == FINISHED) {
        printf("完成时间： %d\t周转时间：%.2lf\t带权周转时间：%.2lf\n",
               j->ftime,
               turnover_time,
               weighted_turnover_time);
    }
    
    printf("资源要求：\n");
    llist_for_each(r, j->res)
        resource_info("\t%s：\t%d\n", r);
}


int
job_is_runnable(const int tick, const struct resource *res, struct job *j)
{
    struct resource *r;

    if (j->status != STANDBY)
        return 0;

    // 尚未到就绪时间
    if (tick < j->atime)
        return 0;

    llist_for_each(r, j->res)
        if (!resource_check_quota(res, r->name, r->quota))
            return 0;

    return 1;
}

static struct job *
__find_mid(struct job *list)
{
    struct job *slow, *fast;

    if (list == NULL)
        return NULL;

    slow = list; fast = list;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

static struct job *
__merge(struct job *left, struct job *right,
        int (*compar)(const struct job a, const struct job b))
{
    struct job *head, *prev, *p;

    head = NULL;
    p = head;
    while (left != NULL && right != NULL) {
        if (compar(*left, *right) <= 0) {
            p = left;
            left = left->next;
        } else {
            p = right;
            right = right->next;
        }

        if (head == NULL)
            head = p;
        else
            prev->next = p;
        prev = p;
    }
    
    if (left == NULL)
        prev->next = right;
    else
        prev->next = left;

    return head;
}

static struct job *
__sort(struct job *head,
       int (*compar)(const struct job a, const struct job b))
{
    struct job *mid, *left, *right;

    if (head == NULL || head->next == NULL)
        return head;

    left = head;
    mid = __find_mid(head);
    right = mid->next;
    mid->next = NULL;

    return __merge(__sort(left, compar), __sort(right, compar), compar);
}

void
job_sort(struct job **jobs,
         int (*compar)(const struct job a, const struct job b))
{
    *jobs = __sort(*jobs, compar);
}
