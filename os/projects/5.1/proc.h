#ifndef PROC_H
#define PROC_H

#include "config.h"
#include "fs.h"

struct proc {
    struct file *opened_file[NO_FILE];          // 当前打开的文件描述符
    struct inode *cwd;                          // 当前目录
};

#endif /* #ifndef PROC_H */
