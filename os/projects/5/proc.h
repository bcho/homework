#ifndef PROC_H
#define PROC_H

#include "config.h"

struct user {
    int id;                     // 用户 id
    char *name[NAME_LENGTH];    // 用户名称
};


// 获取用户 id
//
// @param 用户
int user_get_id(struct user *);

#endif
