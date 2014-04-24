/* queue.c: 队列相关操作的实现 */

#include "str.h"
#include "utils.h"
#include "queue.h"


struct queue *queue_init(char **values, int count)
{
    int i;
    struct queue *q;
    
    q = (struct queue *) Malloc(sizeof(struct queue));
    q->l = 0;
    q->r = -1;
    q->buffer = (char **) Malloc(sizeof(char *) * count);
    for (i = 0; i< count; i++)
        queue_enqueue(q, values[i]);

    return q;
}

void queue_destory(struct queue *q)
{
    int i;

    for (i = 0; i < q->r; i++)
        free(q->buffer[i]);
    free(q->buffer);
}

char *queue_pop(struct queue *q)
{
    char *rv;

    Assert(q->r - q->l >= 0);
    rv = q->buffer[q->l];
    q->l = q->l + 1;

    return rv;
}

char *queue_first(struct queue *q)
{
    Assert(q->r - q->l >= 0);
    return q->buffer[q->l];
}

void queue_enqueue(struct queue *q, char *value)
{
    q->r = q->r + 1;
    q->buffer[q->r] = str_copy(value);
}
