#include "proc.h"
#include "sched.h"

// 按最高优先度调度算法
// 
// 生成 n 个进程：
// $ ./priority_sched n [NTIME_ALGO] [PRIORITY_ALGO]

int
main(int argc, char *argv[])
{
    int proc_count;
    enum dist_algo ntime_algo, pri_algo;
    struct proc *procs;

    PARSE_CLI(argc, argv, proc_count, ntime_algo, pri_algo);
    PREPARE_PROCS(procs, proc_count, ntime_algo, pri_algo);

    printf("总运行时间片: %d\n", schedule(procs));

    return 0;
}

static int
high_prioriry_first(struct proc a, struct proc b)
{
    return b.priority - a.priority;
}

int
schedule(struct proc *procs)
{
    int total_ran_time, ran_time;

    struct proc ready, finished;
    struct proc *proc;

    ready.next = procs;
    finished.next = NULL;

    total_ran_time = 0;
    while (ready.next != NULL) {
        // 按照优先度进行排序
        proc_sort(&ready.next, high_prioriry_first);

        proc = ready.next;
        printf("当前运行进程: %s\n", proc->name);

        // 运行进程
        proc->state = RUNNING;
        ran_time = proc_run(proc);
        total_ran_time = total_ran_time + ran_time;

        proc_info(*proc);

        if (proc->state == FINISHED) {               // 进程已经结束
            proc_pop(&ready, proc);
            proc_insert(&finished, proc);
        } else {                                     // 更新进程优先度
            proc->state = WAITING;
            proc->priority = proc->priority - 1;
        }
    }

    proc_destory_list(finished.next);

    return total_ran_time;
}
