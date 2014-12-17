#ifndef SYS_CALL_H
#define SYS_CALL_H

#include "proc.h"

// 初始化系统
int init();

// 结束系统
int cleanup();

// 添加一个用户
//
// 返回新建用户 id
//
// @param 用户名
int useradd(const char *);

// 根据用户 id 获取一个用户记录
// 
// @param 用户 id
// @param 用户结构体
int user_get_by_id(int, struct user *);

// 打开一个文件
//
// 成功打开返回文件描述符
//
// @param 当前用户
// @param 文件路径
int open(const struct user *, const char *);

// 关闭一个文件
//
// @param 文件描述符
int close(int);

// 从一个文件读取内容
//
// @param 文件描述符
// @param 内容写入缓存
int read(int, char *);

// 向一个文件写入内容
//
// @param 文件描述符
// @param 写入内容
int write(int, const char *);

// 删除一个文件/文件夹
//
// @param 当前用户
// @param 文件/文件夹路径
int delete(const struct user *, const char *);

// 创建一个文件/文件夹
//
// @param 当前用户
// @param 文件/文件夹路径
// @param 文件/文件夹所有者权限
// @param 其他访问者权限
int create(const struct user *, const char *, unsigned int, unsigned int);

// 将一个文件/文件夹移动到指定文件夹下
//
// @param 当前用户
// @param 源文件/文件夹路径
// @param 目标文件夹路径
int mv(const struct user *, const char *, const char *);

#endif /* #ifndef SYS_CALL_H */
