#ifndef HEAP_H
#define HEAP_H

typedef int element_t;
struct heap_r {
    int capacity, size;
    element_t *array;
};
typedef struct heap_r *heap_t;

heap_t create_heap(int capacity);
void dispose_heap(heap_t q);
void build_heap(heap_t q);
void make_empty_heap(heap_t q);
void insert(element_t x, heap_t q);
element_t pop_min(heap_t q);
element_t get_min(heap_t q);
int is_empty(heap_t q);
int is_full(heap_t q);

#define HEAP_MAX_SIZE 1000
#define EMPTY_ERR (-1)

#endif
