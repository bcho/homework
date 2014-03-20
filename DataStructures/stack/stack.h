#ifndef STACK_H
#define STACK_H

struct stack {
    int capacity;
    int top;
    char *buffer;
};

struct stack *stack_init(int);
void stack_destory(struct stack *);

int stack_is_empty(struct stack *);
int stack_is_full(struct stack *);
char stack_pop(struct stack *);
char stack_top(struct stack *);
void stack_push(struct stack *, const char);

#endif
