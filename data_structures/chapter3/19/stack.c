#include <stdlib.h>
#include "stack.h"

stack_t create_stack(int capacity)
{
    stack_t s = malloc(sizeof(struct stack_r));
    if (s == NULL)
        return NULL;
    s->capacity = capacity;
    s->top = STACK_BOTTOM;
    s->array = malloc(sizeof(element_t) * s->capacity);
    if (s == NULL)
        return NULL;
    return s;
}

void dispose_stack(stack_t stack)
{
    free(stack->array);
    free(stack);
}

int is_empty(stack_t stack)
{
    return (stack->top == STACK_BOTTOM);
}

int is_full(stack_t stack)
{
    return (stack->top == stack->capacity - 1);
}

void pop(stack_t stack)
{
    if (!is_empty(stack))
        stack->top--;
}

void push(element_t x, stack_t stack)
{
    if (!is_full(stack))
        stack->array[++stack->top] = x;
}

int top(stack_t stack)
{
    if (!is_empty(stack))
        return stack->array[stack->top];
    return -1;
}
