#ifndef MEM_DEV_H
#define MEM_DEV_H

// 初始化内存 fs 分区
// 
// @param 分区大小（字节）
void mem_dev_init(unsigned int);

// 从内存分区读取一个块
//
// @param 块号
unsigned char *mem_dev_read(unsigned int);

// 写入一个块到内存分区中
//
// @param 写入内存的数据
// @param 块号
void mem_dev_write(unsigned char *, unsigned int);

// 销毁一块内存分区缓冲数据
//
// @param 缓冲数据
void mem_dev_free(unsigned char *);

#endif /* #ifndef MEM_DEV_H */
