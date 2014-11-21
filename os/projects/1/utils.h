#ifndef UTILS_H
#define UTILS_H


// 标准正态分布常量
#define ND_MEAN 0
#define ND_STD_DEV 1

#define ABS(x) ((x) < 0) ? (- (x)) : (x)


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
