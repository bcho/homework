#ifndef ARRAY_H
#define ARRAY_H

#define T array_t
typedef struct T *T;

void array_init(T array, int length, int size, void *ary);
T array_new(int length, int size);
void array_free(T *array);
int array_length(T array);
int array_size(T array);
void *array_get(T array, int i);
void *array_put(T array, int i, void *elem);
void array_resize(T array, int length);
T array_copy(T array, int length);

#endif
