#ifndef DOUBLE_STACK_H
#define DOUBLE_STACK_H

typedef char element_t;
struct double_stack_r {
    int capacity;
    int atop, btop;
    element_t *array;
};
typedef struct double_stack_r *double_stack_t;

double_stack_t create_stack(int capacity);
void dispose_stack(double_stack_t s);
int is_empty_a(double_stack_t s);
int is_empty_b(double_stack_t s);
int is_empty(double_stack_t s);
int is_full(double_stack_t s);
void push_a(element_t x, double_stack_t s);
void push_b(element_t x, double_stack_t s);
element_t top_a(double_stack_t s);
element_t top_b(double_stack_t s);
void pop_a(double_stack_t s);
void pop_b(double_stack_t s);

#define EMPTY_ERR -1

#endif
