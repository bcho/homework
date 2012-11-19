#include <stdlib.h>
#include "double_stack.h"

double_stack_t create_stack(int capacity)
{
    double_stack_t s = malloc(sizeof(struct double_stack_r));
    if (s == NULL)
        return NULL;
    s->capacity = capacity;
    s->atop = -1; s->btop = capacity;
    s->array = malloc(sizeof(element_t) * s->capacity);
    if (s->array == NULL)
        return NULL;
    return s;
}

void dispose_stack(double_stack_t s)
{
    free(s->array);
    free(s);
}

int is_empty_a(double_stack_t s)
{
    return (s->atop == -1);
}

int is_empty_b(double_stack_t s)
{
    return (s->btop == s->capacity);
}

int is_empty(double_stack_t s)
{
    return (is_empty_a(s) && is_empty_b(s));
}

int is_full(double_stack_t s)
{
    return (s->atop + 1 == s->btop);
}

void push_a(element_t x, double_stack_t s)
{
    if (!is_full(s))
        s->array[++s->atop] = x; }

void push_b(element_t x, double_stack_t s)
{
    if (!is_full(s))
        s->array[--s->btop] = x;
}

element_t top_a(double_stack_t s)
{
    if (!is_empty_a(s))
        return s->array[s->atop];
    return EMPTY_ERR;
}

element_t top_b(double_stack_t s)
{
    if (!is_empty_b(s))
        return s->array[s->btop];
    return EMPTY_ERR;
}

void pop_a(double_stack_t s)
{
    if (!is_empty_a(s))
        s->atop--;
}

void pop_b(double_stack_t s)
{
    if (!is_empty_b(s))
        s->btop++;
}
