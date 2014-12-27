#ifndef CONFIG_H
#define CONFIG_H

// 物理地址长度
#define PAWIDTH 14

// 虚拟地址长度
#define VAWIDTH 16

// 页面内地址长度
#define PGWIDTH 10

// 内存大小
#define PMEM (1 << PAWIDTH)

// 虚拟内存大小
#define VMEM (1 << VAWIDTH)

#define PTXSHIFT (PGWIDTH)
#define FRXSHIFT (PGWIDTH)

// 物理页数
#define NPPG (1 << (PAWIDTH - FRXSHIFT))

// 虚拟页数
#define NVPG (1 << (VAWIDTH - PTXSHIFT))

#endif /* #ifndef CONFIG_H */
