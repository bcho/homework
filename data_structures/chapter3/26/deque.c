#include <stdlib.h>
#include "deque.h"

queue_t create_queue(int capacity)
{
    queue_t q = malloc(sizeof(struct queue_r));
    if (q == NULL)
        return NULL;
    q->capacity = capacity;
    q->length = 0;
    q->head = q->capacity - 1;
    q->tail = 0;
    q->array = malloc(sizeof(element_t) * q->capacity);
    if (q->array == NULL)
        return NULL;
    return q;
}

void dispose_queue(queue_t q)
{
    free(q->array);
    free(q);
}

int is_full(queue_t q)
{
    return (q->length == q->capacity);
}

int is_empty(queue_t q)
{
    return (q->length == 0);
}

static int forward(int current, int capacity)
{
    return (current + 1) % capacity;
}

static int backward(int current, int capacity)
{
    return (current - 1 + capacity) % capacity;
}

void push(element_t x, queue_t d)
{
    if (!is_full(d)) {
        d->head = backward(d->head, d->capacity);
        /* make the tail point to head */
        if (is_empty(d))
            d->tail = d->head;
        d->array[d->head] = x;
        d->length++;
    }
}

element_t pop(queue_t d)
{
    if (!is_empty(d)) {
        element_t ret = d->array[d->head];
        d->head = forward(d->head, d->capacity);
        d->length--;
        return ret;
    }
    return -1;
}

void inject(element_t x, queue_t d)
{
    if (!is_full(d)) {
        d->tail = forward(d->tail, d->capacity);
        /* make the head point to tail */
        if (is_empty(d))
            d->head = d->tail;
        d->array[d->tail] = x;
        d->length++;
    }
}

element_t eject(queue_t d)
{
    if (!is_empty(d)) {
        element_t ret = d->array[d->tail];
        d->tail = backward(d->tail, d->capacity);
        d->length--;
        return ret;
    }
    return -1;
}

void visit(queue_t d, void (*visit)(element_t x))
{
    if (is_empty(d))
        return;
    int i;
    for (i = d->head;i != d->tail;i = forward(i, d->capacity))
        visit(d->array[i]);
    visit(d->array[d->tail]);
}

void visit_r(queue_t d, void (*visit)(element_t x))
{
    if (is_empty(d))
        return;
    int i;
    for (i = d->tail;i != d->head;i = backward(i, d->capacity))
        visit(d->array[i]);
    visit(d->array[d->head]);
}
