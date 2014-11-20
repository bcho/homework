#ifndef PROCESS_H
#define PROCESS_H

#define PROCESS_NAME_LENGTH 16

enum procstate { WAITING, RUNNING, FINISHED };

struct proc {
    int pid;                            // 进程状态
    enum procstate state;               // 进程状态
    char name[PROCESS_NAME_LENGTH];     // 进程名称
    int priority;                       // 进程优先度

    int ntime;                          // 进程需要运行时间片
    int rtime;                          // 进程已经运行时间片

    // 方便实现按优先度排序的调度算法
    struct proc **pprev;                 // 进程链表前继
    struct proc *next;                  // 进程链表后继
};


// 创建一个进程
//
// 进程初始状态为 ``WAITING``
//
// @param 进程 id
// @param 进程优先度
// @param 进程需要时间片
struct proc *proc_create(int, int, int);

// 销毁一个进程
//
// @param 进程
void proc_destory(struct proc *);

// 打印一个进程信息
//
// @param 进程
void proc_info(struct proc);


#endif /* #ifndef PROCESS_H */
