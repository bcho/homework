// 生成访问指令地址
//
// - 50% 从 0 开始顺序访问
// - 25% 从前半段地址中产生
// - 25% 从后半段地址中产生

#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 生成一个 [lower, upper] 区间内的随机数
int
rand_in(int lower, int upper)
{
    int r;

    r = rand() % (upper - lower + 1);

    return r + lower;
}

int
main(int argc, char *argv[])
{
    int total, i;

    if (argc < 2) {
        total = VMEM;
    } else {
        total = atoi(argv[1]);
    }

    total = MIN(total, VMEM);

    // 顺序访问
    for (i = 0; i < total / 2; i++)
        printf("%d\n", i);
    
    // 打印内存情况
    printf("%d\n", INST_VMDUMP);

    srand(time(NULL));

    // 25% 前半段
    for (i = 0; i < total / 4; i++)
        printf("%d\n", rand_in(0, VMEM / 2));
    
    // 打印内存情况
    printf("%d\n", INST_VMDUMP);
    
    // 25% 后半段
    for (i = 0; i < total / 4; i++)
        printf("%d\n", rand_in(VMEM / 2, VMEM));

    // 打印内存情况
    printf("%d\n", INST_VMDUMP);

    // 退出执行
    printf("%d\n", INST_FINISH);

    return 0;
}
