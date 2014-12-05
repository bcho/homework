#ifndef RESOURCE_H
#define RESOURCE_H

#include "structure.h"

// 创建资源描述
//
// @param 资源名称
// @param 资源配额
struct resource *resource_create(const char *, int);

// 销毁资源配额
//
// @param 待销毁资源
void resource_destroy(struct resource *);

// 查看一个资源配额
//
// @param 资源配额
void resource_info(const char *, struct resource *);

// 登记资源描述
//
// 返回登记资源结点
//
// @param 资源描述链表头
// @param 资源名称
// @param 资源配额
struct resource *resource_append(struct resource **, const char *, int);

// 根据资源名称获取一个资源描述
//
// 当指定资源不存在，返回 0
//
// @param 资源描述链表头
// @param 资源名称
struct resource *resource_get_by_name(const struct resource *, const char *);

// 获取指定资源的配额
//
// 当指定资源不存在，返回 0
//
// @param 资源描述链表头
// @param 资源名称
int resource_get_quota(const struct resource *, const char *);

// 检查指定资源是否有足够配额
//
// 当指定资源不存在，返回假
//
// @param 资源描述链表头
// @param 资源名称
// @param 需要配额
int resource_check_quota(const struct resource *, const char *, int);

#endif  /* #ifndef RESOURCE_H */
