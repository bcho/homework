#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define max(a, b) ((a) > (b)) ? (a) : (b)

int is_empty(queue_t q)
{
    return (q->size == 0);
}

int is_full(queue_t q)
{
    return (q->size == q->capacity);
}

queue_t create_queue(int max_elements)
{
    queue_t q = malloc(sizeof(struct queue_struct));
    if (q == NULL) {
        printf("Out of memory!");
    } else {
        q->capacity = max(max_elements, MIN_QUEUE_SIZE);
        q->front = 0;
        q->tail = (q->front - 1 + q->capacity) % q->capacity;
        q->array = malloc(sizeof(element_t) * q->capacity);
        if (q->array == NULL)
            printf("Out of memory!");
    }
    return q;
}

void dispose_queue(queue_t q)
{
    free(q->array);
    free(q);
}

void make_empty(queue_t q)
{
    q->size = 0;
    q->tail = (q->front - 1 + q->capacity) % q->capacity;
}

void enqueue(element_t x, queue_t q)
{
    if (!is_full(q)) {
        q->tail = (q->tail + 1) % q->capacity;
        q->array[q->tail] = x;
        q->size++;
    } else {
        printf("queue is full");
    }
}

element_t front(queue_t q)
{
    if (!is_empty(q)) {
        return q->array[q->front];
    } else {
        printf("queue is empty");
    }
    return '0';
}

void dequeue(queue_t q)
{
    if (!is_empty(q)) {
        q->front = (q->front + 1) % q->capacity;
        q->size--;
    } else {
        printf("queue is empty");
    }
}
