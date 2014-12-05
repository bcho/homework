#ifndef JOB_H
#define JOB_H

#include "structure.h"

// 创建一个作业
//
// @param 用户名
// @param 作业名
// @param 就绪时间
// @param 运行时间
// @param 所需资源描述链
struct job *job_create(const char *,
                       const char *,
                       int,
                       int,
                       struct resource *);

// 销毁一个作业
//
// @param 待销毁作业
void job_destroy(struct job *);

// 运行一个作业
//
// @param 作业
int job_run(struct job *);

// 查看一个作业情况
//
// @param 作业
void job_info(struct job *);

// 计算作业链表运行情况
//
// @param 作业链表
void job_list_info(struct job *);

// 检查作业是否可以运行
//
// @param 系统时间
// @param 系统资源状况
// @param 作业
int job_is_runnable(const int, const struct resource *, struct job *);

// 对作业链表进行排序
//
// @param 链表指针
// @param 比较函数
void job_sort(struct job **,
              int (*compar)(const struct job, const struct job));

#endif  /* #ifndef JOB_H */
