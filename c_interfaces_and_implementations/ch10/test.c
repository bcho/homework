#include <stdio.h>

#include "array.h"

int main()
{
    array_t darray;
    int i, length;

    length = 15;
    darray = array_new(length, (int) sizeof(int));
    for (i = 0;i < length;i++)
        array_put(darray, i, &length);

    for (i = 0;i < length;i++)
        printf("%d ", *((int *) array_get(darray, i)));
    printf("\n");

    array_resize(darray, length - 1);
    printf("%d", array_length(darray));

    array_free(&darray);
    
    return 0;
}
