#include "stack.h"

#include <stdlib.h>


struct stack *stack_init(int capacity)
{
    struct stack *s;

    s = malloc(sizeof(struct stack));
    if (s == NULL)
        return NULL;
    s->buffer = malloc(sizeof(char) * capacity);
    if (s->buffer == NULL)
        return NULL;

    s->capacity = capacity;
    s->top = -1;

    return s;
}

void stack_destory(struct stack *s)
{
    free(s->buffer);
    free(s);
}

int stack_is_empty(struct stack *s)
{
    return (s->top < 0);
}

int stack_is_full(struct stack *s)
{
    return (s->top > s->capacity - 1);
}

char stack_pop(struct stack *s)
{
    int pos;

    if (stack_is_empty(s))
        return 0;

    pos = s->top;
    s->top = s->top - 1;
    return *(s->buffer + pos);
}

char stack_top(struct stack *s)
{
    if (stack_is_empty(s))
        return 0;

    return *(s->buffer + s->top);
}

void stack_push(struct stack *s, const char e)
{
    if (stack_is_full(s))
        return;

    s->top = s->top + 1;
    *(s->buffer + s->top) = e;
}
