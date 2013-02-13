#include <stdio.h>
#include <assert.h>

#include "io.h"
#include "grid.h"

void fill_grid(struct grid_t *grid, int e);

int main()
{
    struct grid_t *grid_a, *grid_b;

    grid_a = grid_init(5, 5);
    grid_b = grid_init(5, 5);

    fill_grid(grid_a, 5);
    fill_grid(grid_b, 2);

    assert(grid_retrieve(grid_a, 2, 1) == 5);
    assert(grid_retrieve(grid_b, 4, 4) == 2);

    grid_cpy(grid_a, grid_b);
    assert(grid_cmp(grid_a, grid_b) == 0);
    assert(grid_retrieve(grid_a, 2, 1) == 5);
    
    grid_set(grid_a, 0, 0, 0);
    print_grid(grid_a, 'X', '-');
    printf("%d", grid_retrieve(grid_a, 0, 0));

    return 0;
}

void fill_grid(struct grid_t *grid, int e)
{
    int i, j;

    for (i = 0;i < grid->rows;i++)
        for (j = 0;j < grid->cols;j++)
            grid_set(grid, i, j, e);
}
