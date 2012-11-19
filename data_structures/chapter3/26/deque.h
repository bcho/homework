#ifndef DEQUE_H
#define DEQUE_H

typedef char element_t;
struct queue_r {
    int capacity, length;
    int head, tail;
    element_t *array;
};
typedef struct queue_r *queue_t;

queue_t create_queue(int capacity);
void dispose_queue(queue_t q);

int is_full(queue_t q);
int is_empty(queue_t q);

void push(element_t x, queue_t d);
element_t pop(queue_t d);
void inject(element_t x, queue_t d);
element_t eject(queue_t d);
void visit(queue_t d, void (*visit)(element_t x));
void visit_r(queue_t d, void (*visit)(element_t x));
#endif
