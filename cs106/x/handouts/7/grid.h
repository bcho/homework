#ifndef GRID_H
#define GRID_H

typedef int grid_element_t;
struct grid_t {
    int cols, rows;
    grid_element_t *grid;
};

#define T struct grid_t

T *grid_init(int rows, int cols);
void grid_free(T *grid);
grid_element_t grid_retrieve(T *grid, int x, int y);
void grid_set(T *grid, int x, int y, grid_element_t element);
void grid_cpy(T *src, T *dest);
void grid_fill(T *grid, grid_element_t element);
int grid_cmp(T *a, T *b);

#undef T

#endif
