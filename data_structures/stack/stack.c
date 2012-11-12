#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

element_t *new_array(int size)
{
    element_t *array;

    array = malloc(sizeof(element_t) * size);
    if (array == NULL)
        printf("Out of memory!");
    return array;
}

void free_array(element_t *array)
{
    free(array);
}

int is_empty(stack_t s)
{
    return (s->top == EMPTY_TOS);
}

int is_full(stack_t s)
{
    return (s->top == s->capacity);
}

stack_t create_stack(int max_elements)
{
    stack_t s;

    s = malloc(sizeof(struct stack_struct));
    if (s == NULL) {
        printf("Out of memory!");
        return s;
    }
    s->capacity = (max_elements > MIN_STACK_SIZE) ? \
                  max_elements : MIN_STACK_SIZE;
    s->top = EMPTY_TOS;
    s->array = new_array(s->capacity);
    return s;
}

void dispose_stack(stack_t s)
{
    if (s != NULL) {
        free_array(s->array);
        free(s);
    }
}

void make_empty(stack_t s)
{
    s->top = EMPTY_TOS;
}

void push(element_t x, stack_t s)
{
    s->array[++s->top] = x;
}

element_t top(stack_t s)
{
    if (!is_empty(s))
        return s->array[s->top];
    else
        printf("Stack is empty!");
    return 0;
}

void pop(stack_t s)
{
    if (!is_empty(s))
        s->top--;
    else
        printf("Stack is empty!");
}
