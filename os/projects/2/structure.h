#ifndef STRUCTURE_H
#define STRUCTURE_H

#define NAME_LENGTH 32

struct resource {
    char name[NAME_LENGTH];             // 资源名称
    int quota;                          // 资源数量

    struct resource *next;              // 资源链表域
};

enum job_status { STANDBY, RUNNING, FINISHED };

struct job {
    char user[NAME_LENGTH];             // 用户名
    char name[NAME_LENGTH];             // 作业名
    enum job_status status;             // 作业状态
    int atime;                          // 就绪时间
    int ftime;                          // 完成时间
    int rtime;                          // 运行时间
    struct resource *res;               // 所需资源

    struct job *next;                   // 作业链表域
};

// 调度实现接口定义
//
// @param 可执行作业链表
// @param 完成的作业结点
typedef int scheduler_fn(struct job *, struct job **);

#endif  /* #ifndef STRUCTURE_H */
