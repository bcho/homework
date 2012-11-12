#ifndef STACK_H
#define STACK_H

typedef char element_t;
struct stack_struct;
typedef struct stack_struct *stack_t;

int is_empty(stack_t s);
int is_full(stack_t s);
stack_t create_stack(int max_elements);
void dispose_stack(stack_t s);
void make_empty(stack_t s);
void push(element_t x, stack_t s);
element_t top(stack_t s);
void pop(stack_t s);

#define EMPTY_TOS -1
#define MIN_STACK_SIZE 5

struct stack_struct {
    int capacity;
    int top;
    element_t *array;
};
#endif
