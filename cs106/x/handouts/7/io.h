#ifndef IO_H
#define IO_H

#include "grid.h"

void print_grid(struct grid_t *grid, char alive, char dead);
struct grid_t *init_grid_from_file(char *fname, int max_cols, \
                                   char comment, char alive, char dead);
struct grid_t *init_grid_from_random();

#endif
