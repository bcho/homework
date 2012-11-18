#ifndef STACK_H
#define STACK_H

typedef int element_t;
struct stack_r {
    int top, capacity;
    element_t *array;
};
typedef struct stack_r *stack_t;

stack_t create_stack(int capacity);
void dispose_stack(stack_t stack);
int is_empty(stack_t stack);
int is_full(stack_t stack);
void pop(stack_t stack);
void push(element_t x, stack_t stack);
element_t top(stack_t stack);

#define STACK_BOTTOM -1
#endif
