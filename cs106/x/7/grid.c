#include <stdlib.h>
#include <assert.h>

#include "grid.h"

#define T struct grid_t

T *grid_init(int rows, int cols)
{
    T *grid;

    assert(cols > 0 && rows > 0);

    grid = malloc(sizeof(T));
    assert(grid != NULL);
    grid->cols = cols;
    grid->rows = rows;
    grid->grid = malloc(sizeof(grid_element_t) * cols * rows);
    assert(grid->grid != NULL);

    return grid;
}

void grid_free(T *grid)
{
    assert(grid != NULL && grid->grid != NULL);
    free(grid->grid);
    free(grid);
}

grid_element_t grid_retrieve(T *grid, int x, int y)
{
    assert(grid != NULL && grid->grid != NULL);
    assert(x < grid->rows && y < grid->cols);
    return *(grid->grid + x * grid->cols + y);
}

void grid_set(T *grid, int x, int y, grid_element_t element)
{
    assert(grid != NULL && grid->grid != NULL);
    assert(x < grid->rows && y < grid->cols);
    grid->grid[x * grid->cols + y] = element; 
}

void grid_cpy(T *src, T *dest)
{
    int i;

    assert(src != NULL && src->grid != NULL && \
            dest != NULL && dest->grid != NULL);
    assert(src->cols <= dest->cols && src->rows <= dest->rows);

    dest->cols = src->cols;
    dest->rows = dest->rows;
    for (i = 0;i < src->cols * src->rows;i++)
        dest->grid[i] = src->grid[i];
}

void grid_fill(T *grid, grid_element_t element)
{
    int i;
    
    assert(grid != NULL);

    for (i = 0;i < grid->cols * grid->rows;i++)
        grid_set(grid, i / grid->cols, i % grid->cols, element);
}


int grid_cmp(T *a, T *b)
{
    int i;

    if (a->rows != b->rows || a->cols != b->cols)
        return -1;
    for (i = 0;i < a->rows * a->cols;i++)
        if (grid_retrieve(a, i / a->cols, i % a->cols) != \
                grid_retrieve(b, i / b->cols, i % b->cols))
            return -1;
    return 0;
}
