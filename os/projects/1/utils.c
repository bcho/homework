#include "utils.h"

#include <math.h>
#include <stdlib.h>

#define ND_MEAN 0                           // 使用标准正态分布
#define ND_STD_DEV 1

void
make_increment_seq(int n, double *seq)
{
    for (; n > 0; n--)
        seq[n - 1] = n;
}

// 使用 Marsaglia polar 方法从正态分布 N(mean, std_dev^2)
// 中生成一个值。
//
// 奇数次调用会生成一个新值，偶数次调用会生成上一次调用的对称值。
//
// Ref: https://en.wikipedia.org/wiki/Marsaglia_polar_method
//
// TODO windows compatible
//
// @param 位置参数
// @param 尺度参数
static double
normal_distribution_randn(const double mean, const double std_dev)
{
    static int ready = 0;
    static double x, y;                     // 上次生成的基准值
    double u, v, s;

    if (ready) {                            // 上次已经生成一个基准值
        ready = !ready;
        return mean + std_dev * y;
    }

    do {
        u = (rand() / ((double) RAND_MAX)) * 2 - 1;
        v = (rand() / ((double) RAND_MAX)) * 2 - 1;
        s = u * u + v * v;
    } while (s >= 1 || s == 0);

    s = sqrt(-2 * log(s) / s);
    x = u * s;
    y = v * s;

    ready = 1;
    return mean + std_dev * x;
}

void
make_normal_distribution_seq(int n, double *seq)
{
    for (; n > 0; n--)
        seq[n - 1] = normal_distribution_randn(ND_MEAN, ND_STD_DEV);
}
