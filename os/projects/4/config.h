#ifndef CONFIG_H
#define CONFIG_H

// 总内存大小（bytes）
#define MEM_SIZE (640 * 1024)

// 系统内存大小（bytes）
#define OS_MEM_SIZE (40 * 1024)

// 用户内存大小（bytes）
#define USER_MEM_SIZE (MEM_SIZE - OS_MEM_SIZE)

#endif  /* #ifndef CONFIG_H */
