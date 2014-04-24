#ifndef QUEUE_H
#define QUEUE_H

/* 队列结构体的定义 */
struct queue {
    char **buffer;
    int l, r;
};

/*
 * 初始化队列
 *
 * :param values: 初始化的队列元素
 * :param count: 初始化队列元素个数
 * :rtype: struct queue *
 */
struct queue *queue_init(char **values, int count);

/*
 * 销毁一个队列
 *
 * :param q: 被销毁的队列
 */
void queue_destory(struct queue *q);

/*
 * 获取队列的第一个元素
 *
 * .. note:: 返回的是队首元素的值
 *
 * :param q: 队列
 * :rtype: char *
 */
char *queue_first(struct queue *q);

/*
 * 从队列移出一个元素
 *
 * .. note:: 返回的是队首元素的值
 *
 * :param q: 队列
 * :rtype: char *
 */
char *queue_pop(struct queue *q);

/*
 * 向队列添加元素
 *
 * .. note:: 添加元素会被复制到队列里
 *
 * :param q: 队列
 * :param value: 添加进队列的元素
 */
void queue_enqueue(struct queue *q, char *value);

#endif
