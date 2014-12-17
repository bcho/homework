#ifndef PROC_H
#define PROC_H

#include "config.h"

struct user {
    int id;                     // 用户 id
    char name[NAME_LENGTH];     // 用户名称
};

// 创建一个用户
//
// @param 用户 id
// @param 用户名
struct user *user_create(int, const char *);

// 销毁一个用户
//
// @param 用户
void user_destory(struct user *);

// 获取用户 id
//
// @param 用户
int user_get_id(struct user *);

#endif
