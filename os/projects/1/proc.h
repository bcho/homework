#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_NAME_LENGTH 16

// 进程状态
enum procstate { WAITING, RUNNING, FINISHED };

// 进程运行错误代码
#define E_UNRUNABLE 0x001

// 分布算法
enum dist_algo {
    MEAN,                               // 等值分布
    INCR,                               // 递增分布
    NORM                                // 正态分布
};

struct proc {
    int pid;                            // 进程状态
    enum procstate state;               // 进程状态
    char name[PROCESS_NAME_LENGTH];     // 进程名称
    double priority;                    // 进程优先度

    int ntime;                          // 进程需要运行时间片
    int rtime;                          // 进程已经运行时间片

    // 方便实现按优先度排序的调度算法
    struct proc *next;                  // 进程链表后继
};


// 创建一个进程
//
// 进程初始状态为 ``WAITING``
//
// @param 进程 id
// @param 进程优先度
// @param 进程需要时间片
struct proc *proc_create(int, double, int);

// 销毁一个进程
//
// @param 进程
void proc_destory(struct proc *);

// 创建若干个进程
//
// 进程初始状态为 ``WAITING``
// 各进程 pid 为在链表中位置
//
// @param 进程数
struct proc *proc_create_list(int);

// 销毁一个进程链
//
// @param 进程链
void proc_destory_list(struct proc *);

// 打印一个进程信息
//
// @param 进程
void proc_info(struct proc);

// 运行一个可运行的进程
//
// 可运行状态指进程状态为 ``RUNNING``
//
// 运行结束后返回进程运行时间片数量
// 如果进程不可运行，返回 ``-E_UNRUNABLE``
//
// 运行结束后增加这个进程的已运行时间片，
// 如果已经达到需要时间片，将进程状态修改为 ``FINISHED``
//
// @param 进程
int proc_run(struct proc *);

// 对一系列进程进行优先度填充
//
// @param 填充分布算法
// @param 进程总数
// @param 进程链表头结点
void proc_fill_priority(enum dist_algo, int, struct proc *);

// 对一系列进程进行时间片长度填充
//
// @param 填充分布算法
// @param 进程总数
// @param 进程链表头结点
void proc_fill_ntime(enum dist_algo, int, struct proc *);


// 遍历一个进程链表
//
// @param 循环变量
// @param 链表头
#define proc_for_each(pos, head) \
    for (pos = (head); pos != NULL; pos = pos->next)


// 插入到链表中
//
// @param 前继
// @param 新结点
#define proc_insert(prev, node) \
        do { \
            node->next = (prev)->next; \
            (prev)->next = node; \
        } while (0)


#endif /* #ifndef PROCESS_H */
