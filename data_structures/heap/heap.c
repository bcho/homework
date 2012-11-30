#include <stdlib.h>
#include <assert.h>
#include "heap.h"

static void swap(element_t *a, element_t *b)
{
    element_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void swim(int start, heap_t q)
{
    int i;
    for (i = start;q->array[i / 2] > q->array[i];i /= 2)
        swap(&q->array[i / 2], &q->array[i]);
}

void sink(int start, heap_t q)
{
    int i, child;
    for (i = start;i * 2 <= q->size;i = child) {
        child = i * 2;
        if (child < q->size && q->array[child] > q->array[child + 1])   /* comapre with the smaller child */
            child++;
        if (q->array[i] > q->array[child])
            swap(&q->array[i], &q->array[child]);
        else
            break;
    }
}

heap_t create_heap(int capacity)
{
    heap_t q;

    assert(capacity < HEAP_MAX_SIZE);

    q = malloc(sizeof(struct heap_r));
    assert(q != NULL);
    q->capacity = capacity;
    q->size = 0;

    q->array = malloc(sizeof(element_t) * (q->capacity + 1));       /* root is in 1 */
    assert(q->array != NULL);
    q->array[0] = EMPTY_ERR;

    return q;
}

void dispose_heap(heap_t q)
{
    assert(q != NULL);
    free(q->array);
    free(q);
}

void build_heap(heap_t q)
{
    int i;
    assert(!is_empty(q));
    /* ensure the smallest node will swim to the top */
    for (i = q->size;i > 0;i--)
        sink(i, q);
}

void make_empty_heap(heap_t q)
{
    q->size = 0;
}

void insert(element_t x, heap_t q)
{
    if (!is_full(q)) {
        q->array[++q->size] = x;
        swim(q->size, q);
    }
}

element_t pop_min(heap_t q)
{
    element_t min;

    if (is_empty(q))
        return EMPTY_ERR;
    min = q->array[1];
    q->array[1] = q->array[q->size--];
    sink(1, q);
    return min;
}

element_t get_min(heap_t q)
{
    if (is_empty(q))
        return EMPTY_ERR;
    return q->array[1];
}

int is_empty(heap_t q)
{
    return (q->size == 0);
}

int is_full(heap_t q)
{
    return (q->size == q->capacity);
}
