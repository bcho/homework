#include "sched.h"

// Round Robin 调度算法
//
// 生成 n 个进程
// $ ./round_robin_sched n [NTIME_ALGO] [PRIORITY_ALGO]


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

int
schedule(struct proc *procs)
{
    int total_ran_time, ran_time;

    struct proc ready, finished;
    struct proc *ready_last, *proc;

    ready.next = procs;
    finished.next = NULL;

    // 获取就绪进程链中的最后一个进程
    proc_for_each(proc, &ready) {
        if (proc->next == NULL) {
            ready_last = proc;
            break;
        }
    }

    for (total_ran_time = 0; ready.next != NULL;) {
        // 选取就绪进程中的第一个进程
        proc_pop(&ready, proc);

        // 运行进程
        proc->state = RUNNING;
        ran_time = proc_run(proc);
        total_ran_time = total_ran_time + ran_time;

        printf("当前运行进程:\n");
        proc_info(*proc);
        printf("\n");
        printf("就绪进程:\n");
        proc_infos(ready.next);
        printf("\n");

        if (proc->state == FINISHED) {              // 进程已经结束运行
            proc_insert(&finished, proc);
        } else {                                    // 加入到就绪队列队尾
            proc->state = WAITING;

            // FIXME special case?
            if (proc == ready_last)
                ready_last = &ready;
            proc_insert(ready_last, proc);
            ready_last = proc;
        }
    }

    proc_destory_list(finished.next);

    return total_ran_time;
}
