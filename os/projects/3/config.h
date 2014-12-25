#ifndef CONFIG_H
#define CONFIG_H

// 物理地址总位数
#define PAWIDTH 13

// 虚拟地址总位数
#define VAWIDTH 16

// 内存大小
#define PMEM (1 << PAWIDTH)

// 虚拟内存大小
#define VMEM (1 << VAWIDTH)

// 页面数偏移
#define PTXSHIFT 10
#define FRXSHIFT 10

// 物理页数
#define NPPG (1 << (PAWIDTH - FRXSHIFT))

// 虚拟页数
#define NVPG (1 << (VAWIDTH - PTXSHIFT))

#endif /* #ifndef CONFIG_H */
