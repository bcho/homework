#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "array.h"

struct array_t {
    int length;
    int size;
    char *array;
};

void array_init(T array, int length, int size, void *ary)
{
    assert(array);
    assert(ary && length > 0 || ary == NULL && length == 0);
    assert(size > 0);
    array->length = length;
    array->size = size;
    array->array = (length > 0) ? (ary) : (NULL);
}

T array_new(int length, int size)
{
    T array;
    array = malloc(sizeof *array);
    if (length > 0)
        array_init(array, length, size, calloc(length, size));
    else
        array_init(array, length, size, NULL);
    return array;
}

void array_free(T *array)
{
    assert(array && *array);
    free((*array)->array);
    free(*array);
}

int array_length(T array)
{
    assert(array);
    return (array->length);
}

int array_size(T array)
{
    assert(array);
    return (array->size);
}

void *array_get(T array, int i)
{
    assert(array);
    assert(i >= 0 && i < array_length(array));
    return array->array + i * array_size(array);
}

void *array_put(T array, int i, void *elem)
{
    assert(array);
    assert(i >= 0 && i < array_length(array));
    assert(elem);
    int elem_size = array_size(array);
    memcpy(array->array + i * elem_size, elem, elem_size);
    return elem;
}

void array_resize(T array, int length)
{
    assert(array);
    assert(length >= 0);
    if (length  == 0)
        free(array->array);
    else if (array_length(array) == 0)
        array->array = malloc(length * array_size(array));
    else
        realloc(array->array, length * array_size(array));
    array->length = length;
}

T array_copy(T array, int length)
{
    T copy;
    int arr_length, arr_size;

    assert(array);
    assert(length >= 0);

    arr_size = array_size(array);
    arr_length = array_length(array);
    copy = array_new(length, array_size(array));
    length = (length > arr_length) ? (length) : (arr_length);
    if (length > 0)
        memcpy(copy->array, array->array, length * arr_size);
    return copy;
}
