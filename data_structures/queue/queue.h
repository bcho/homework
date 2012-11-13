#ifndef QUEUE_H
#define QUEUE_H

typedef char element_t;
struct queue_struct;
typedef struct queue_struct *queue_t;

int is_empty(queue_t q);
int is_full(queue_t q);
queue_t create_queue(int max_elements);
void dispose_queue(queue_t q);
void make_empty(queue_t q);
void enqueue(element_t x, queue_t q);
element_t front(queue_t q);
void dequeue(queue_t q);

#define MIN_QUEUE_SIZE 5

struct queue_struct {
    int capacity;
    int front, tail;
    int size;
    element_t *array;
};
#endif
