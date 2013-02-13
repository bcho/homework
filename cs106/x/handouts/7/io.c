#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "grid.h"
#include "io.h"

void print_grid(struct grid_t *grid, char alive, char dead)
{
    int i, j;

    for (i = 0;i < grid->rows;i++) {
        for (j = 0;j < grid->cols;j++)
            /* TODO use isalive to determine cell's state */
            if (grid_retrieve(grid, i, j))
                printf("%c", alive);
            else
                printf("%c", dead);
        printf("\n");
    }
}

struct grid_t *init_grid_from_file(char *fname, int max_cols, \
                                   char comment, char alive, char dead)
{
    struct grid_t *grid;
    FILE *stream;
    int cols, rows, counter;
    char *line, *c;

    stream = fopen(fname, "r");
    assert(stream != NULL);

    line = malloc(sizeof(char) * max_cols);
    cols = -1;
    rows = -1;
    counter = 0;
    for(;getline(&line, (size_t *) &max_cols, stream) != -1;) {
        if (line[0] != comment) {
            if (rows == -1) {
                rows = atoi(line);
                assert(rows != -1);
            } else if (cols == -1) {
                cols = atoi(line);
                assert(cols != -1);
                grid = grid_init(rows, cols);
                grid_fill(grid, 0);
            } else if (counter < rows * cols) {
                /* read the grid */
                assert(rows != -1 && cols != -1);
                for (c = line;*c != '\n' && *c != EOF;c++, counter++)
                    grid_set(grid, counter / cols, counter % cols,\
                            (*c == alive) ? (1) : (0));
            }
        }
    }
    assert(rows != -1 && cols != -1 && grid != NULL);
    fclose(stream);
    return grid;
}

struct grid_t *init_grid_from_random()
{
    struct grid_t *grid;
    int cols, rows, i, j;

    srandom(time(NULL));
    /* TODO range */
    cols = random() % 21 + 40;
    rows = random() % 21 + 40;
    grid = grid_init(rows, cols);
    grid_fill(grid, 0);
    for (i = 0;i < rows;i++)
        for (j = 0;j < cols;j++)
            grid_set(grid, i, j, random() % 2);
    return grid;
}
