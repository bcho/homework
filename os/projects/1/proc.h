#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_NAME_LENGTH 16

// 进程状态
enum procstate { WAITING, RUNNING, FINISHED };

// 进程运行错误代码
#define E_UNRUNABLE 0x001

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


#endif /* #ifndef PROCESS_H */
