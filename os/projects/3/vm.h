#ifndef VM_H
#define VM_H

// 初始化虚拟内存
void vm_init();

// 访问虚拟内存地址
//
// @param 虚拟内存地址
void vm_hit(unsigned int);

// 为一个虚拟内存页分配一个物理页
//
// @param 虚拟内存页号
void vm_alloc(unsigned int);

// 打印虚拟内存情况
void vm_dump();

#endif /* #ifndef VM_H */
