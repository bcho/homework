#ifndef STR_H
#define STR_H

/*
 * 复制一个字符串
 *
 * :param str: 被复制的字符串
 * :rtype: char *
 */
char *str_copy(char *str);

/*
 * 销毁 `str_copy` 生成的字符串
 *
 * :param str: 被销毁的字符串
 */
void str_copy_destory(char *str);

/*
 * 复制一个字符串的前 n 个字符
 *
 * :param str: 被复制的字符串
 * :param n: 复制字符的数量，如果 n 大于被复制字符串的长度，
 *           则多余位置补 0
 * :rtype: char *
 */
char *str_copyn(char *str, int n);

/*
 * 销毁 `str_copyn` 生成的字符串
 *
 * :param str: 被销毁的字符串
 */
void str_copyn_destory(char *str);

/*
 * 判断字符串的开头是否为给定字符
 *
 * :param str: 字符串
 * :param prefix: 检测字符
 * :rtype: 0 为不是由给定字符开头， 非 0 为由给定字符开头
 */
int str_startswith(char *str, char prefix);

/*
 * 判断字符串的结尾是否为给定字符
 *
 * :param str: 字符串
 * :param suffic: 检测字符
 * :rtype: 0 为不是由给定字符结束， 非 0 为由给定字符结束
 */
int str_endswith(char *str, char suffix);

/*
 * 根据给定字符将字符串进行分割
 *
 * :param str: 被分割的字符串
 * :param delim: 给定字符
 * :param rv: 用作存放分割后的字符串序列
 * :rtype: 分割的段数
 */
int str_split(char *str, char delim, char ***rv);

/*
 * 销毁 `str_split` 生成的字符串序列
 *
 * :param tokens: 被销毁的字符串序列
 * :parma count: 字符串序列的长度
 */
void str_split_destory(char **tokens, int count);

/*
 * 替换字符串内的给定子串
 *
 * :param from: 被替换的字符串
 * :param pattern: 被替换的字串
 * :param replace: 替换的串
 * :rtype: 替换后的字符串
 */
char *str_replace(char *from, char *pattern, char *replace);

/*
 * 销毁 `str_replace` 生成的字符串
 *
 * :param str: 被销毁的字符串
 */
void str_replace_destory(char *str);

#endif
