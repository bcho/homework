#include "proc.h"
#include "sched.h"
#include "utils.h"

#include <stdlib.h>

// 多级反馈队列调度算法
//
// 生成 n 个进程
// $ ./multiple_queue n [NTIME_ALGO] [PRIORITY_ALGO]


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


// 反馈队列数目
#define QUEUE_COUNT 5
// 反馈队列基准时间片数量
#define QUEUE_BASE_SLICES 1

struct proc_queue {
    int slices;                         // 运行时间片数量
    struct proc head;                   // 进程头结点
    struct proc *tail;                  // 指向进程链表的最后一个结点
};

// 创建一个反馈队列
//
// @param 该队列运行时间片数量
struct proc_queue *
proc_queue_create(int slices)
{
    struct proc_queue *q;

    if (slices <= 0)
        goto fail;

    q = malloc(sizeof(struct proc_queue));
    if (q == NULL)
        goto fail;

    q->head.next = NULL;
    q->tail = &q->head;
    q->slices = slices;
    return q;

fail:
    return NULL;
}

// 销毁一个反馈进程队列
//
// @param 反馈队列
void
proc_queue_destory(struct proc_queue *q)
{
    if (q == NULL)
        return;

    free(q);
}

// 将一个进程加入到反馈队列队尾
//
// @param 反馈队列
// @param 进程
void
proc_queue_add(struct proc_queue *q, struct proc *proc)
{
    proc_insert(q->tail, proc);
    q->tail = proc;
}

// 从反馈队列中移出队首进程
//
// 如果队列为空，返回 ``NULL``
//
// @param 反馈队列
struct proc *
proc_queue_pop(struct proc_queue *q)
{
    struct proc *proc;

    proc_pop(&q->head, proc);
    // 移除的是最后一个进程，需要重新设定队尾指针
    if (proc == q->tail)
        q->tail = &q->head;

    return proc;
}

// 检查反馈队列是否为空
//
// @param 反馈队列
int
proc_queue_is_empty(struct proc_queue *q)
{
    return (q->head.next == NULL);
}

int
schedule(struct proc *procs)
{
    int i, slices;
    int total_ran_time, queue_ran_time, ran_time;
    struct proc_queue *queues[QUEUE_COUNT];
    struct proc_queue **q, **next_q;
    struct proc *proc, *next, finished;

    finished.next = NULL;
    total_ran_time = 0;

    // 初始化反馈队列
    slices = QUEUE_BASE_SLICES;
    for (i = 0; i < QUEUE_COUNT; i++) {
        queues[i] = proc_queue_create(slices);
        if (queues[i] == NULL)
            PANIC("创建反馈队列失败");
        slices = 2 * slices;        // i + 1 队列运行的时间片是 i 队列的两倍
    }
    
    // 将所有进程加入到 0 级队列
    for (proc = procs; proc != NULL;) {
        next = proc->next;
        proc_queue_add(queues[0], proc);
        proc = next;
    }

    // 逐级运行队列
    for (q = queues; q < queues + QUEUE_COUNT; q++) {
        // 计算下一个反馈队列。
        // 如果当前队列已经是最后一个队列，则为该队列本身
        next_q = MIN(q + 1, queues + QUEUE_COUNT - 1);

        queue_ran_time = 0;
        i = q - queues + 1;
        printf("=======================================\n");
        printf("开始运行反馈队列 %d\n", i);

        while (! proc_queue_is_empty(*q)) {
            proc = proc_queue_pop(*q);
            printf("当前运行进程：%s\n", proc->name);

            // 运行进程
            ran_time = 0;
            for (slices = (*q)->slices; slices > 0; slices--) {
                proc->state = RUNNING;
                ran_time = ran_time + proc_run(proc);

                // 进程运行结束，提前完成
                if (proc->state == FINISHED)
                    break;
            }
            queue_ran_time = queue_ran_time + ran_time;

            proc_info(*proc);

            if (proc->state == FINISHED)
                proc_insert(&finished, proc);
            else                                    // 将进程加入到下一级队列
                proc_queue_add(*next_q, proc);
        }

        proc_queue_destory(*q);
        printf("反馈队列 %d 运行完毕，运行时间片：%d\n\n", i, queue_ran_time);
        total_ran_time = total_ran_time + queue_ran_time;
    }

    proc_destory_list(finished.next);

    return total_ran_time;
}
