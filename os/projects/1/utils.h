#ifndef UTILS_H
#define UTILS_H

// 分布算法
enum dist_algo {
    MEAN,                               // 等值分布
    INCR,                               // 递增分布
    NORM                                // 正态分布
};


// 正态分布参数
#define ND_MEAN 3
#define ND_STD_DEV 2

#define ABS(x) (((x) < 0) ? (- (x)) : (x))
#define MIN(a, b) ((a) > (b) ? (b) : (a))


// 从字符串输入获取一个分布算法类型
//
// @param 字符串输入
enum dist_algo dist_algo_parse(const char *);

// 生成一个值均为数列长度的数列
//
// @param 数列长度
// @param 产生数列
void make_mean_seq(int, double *);

// 从 1 开始生成一个递增数列
//
// @param 数列长度
// @param 产生数列
void make_increment_seq(int, double *);


// 根据高斯分布随机生成一个数列
//
// @param 数列长度
// @param 产生数列
void make_normal_distribution_seq(int, double *);

#endif /* #ifndef UTILS_H */
