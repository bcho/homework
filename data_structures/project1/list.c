#include <stdlib.h>
#include "list.h"

int *build_ascending_list(int limit)
{
    int *list, i;

    /* need one more room to place N */
    limit = (limit > MAX - 1) ? (MAX) : (limit + 1);
    list = malloc(sizeof(int) * limit);

    if (list != NULL)
        for (i = 0;i <= limit;i++)
            list[i] = i;

    return list;
}

void drop_list(int *list)
{
    free(list);
}
