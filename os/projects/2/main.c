#include "structure.h"
#include "job.h"
#include "resource.h"
#include "tick.h"
#include "sched.h"
#include "utils.h"

#include <stdarg.h>
#include <string.h>

struct resource system_resource;
struct job scheduled_jobs;

// 添加一个待调度作业
//
// @param 用户名
// @param 作业名
// @param 到达时间
// @param 运行时间
// @param 资源需求数量
// @param 资源需求描述
void add_job(const char *, const char *, int, int, int, ...);

// 添加一个系统资源描述
//
// @param 资源名称
// @param 资源数量
void add_resource(const char *, int);

int
main(int argc, char *argv[])
{
    struct job *j;
    system_resource.next = NULL;
    scheduled_jobs.next = NULL;
    scheduler_fn *scheduler;

    if (argc < 2)
        PANIC("./main [fcfs|sjf|hrn]\n");

    if (strcmp(argv[1], "fcfs") == 0) {
        printf("使用先来先服务调度：\n");
        scheduler = fcfs_scheduler;
    } else if (strcmp(argv[1], "sjf") == 0) {
        printf("使用短作业优先调度：\n");
        scheduler = sjf_scheduler;
    } else if (strcmp(argv[1], "hrn") == 0) {
        printf("使用高响应优先调度：\n");
        scheduler = hrn_scheduler;
    }

    // 声明系统资源
    add_resource("主存", 100);
    add_resource("磁带机", 5);

    // 声明作业
    add_job("A", "JOBA", 0,  25, 2, "主存", 20, "磁带机", 2);
    add_job("B", "JOBB", 20, 30, 2, "主存", 60, "磁带机", 1);
    add_job("C", "JOBC", 30, 15, 2, "主存", 45, "磁带机", 3);
    add_job("D", "JOBD", 35, 20, 2, "主存", 10, "磁带机", 2);
    add_job("E", "JOBE", 45, 10, 2, "主存", 25, "磁带机", 3);

    // 运行作业
    tick(system_resource.next, &scheduled_jobs.next, hrn_scheduler);

    // 输出作业运行情况
    printf("\n作业运行情况：\n");
    llist_for_each(j, scheduled_jobs.next)
        job_info(j);
    job_list_info(scheduled_jobs.next);

    // 销毁数据
    job_destroy(scheduled_jobs.next);
    resource_destroy(system_resource.next);
    return 0;
}

struct resource *
vcreate_resource(int count, va_list ap)
{
    int i;
    struct resource head, *r;
    char *name;
    int quota;

    head.next = NULL;
    for (i = 0; i < count; i++) {
        name = va_arg(ap, char *);
        quota = va_arg(ap, int);

        r = resource_create(name, quota);
        llist_insert_after(&head, r);
    }

    return head.next;
}

void
add_job(const char *user,
        const char *name,
        int atime,
        int rtime,
        int res_count, ...)
{
    va_list res_args;
    struct resource *res;
    struct job *j;

    va_start(res_args, res_count);
    res = vcreate_resource(res_count, res_args);
    va_end(res_args);

    j = job_create(user, name, atime, rtime, res);

    llist_insert_after(&scheduled_jobs, j);
}

void
add_resource(const char *name, int quota)
{
    struct resource *r;

    r = resource_create(name, quota);
    llist_insert_after(&system_resource, r);
}
