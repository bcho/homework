#include <stdio.h>

#include "grid.h"
#include "io.h"

int main()
{
    struct grid_t *grid;

    grid = init_grid_from_random();
    printf("%d\n%d\n", grid->rows, grid->cols);
    print_grid(grid, 'X', '-');
    grid_free(grid);

    grid = init_grid_from_file("init_state.in");
    print_grid(grid, 'X', '-');
    grid_free(grid);

    return 0;
}
