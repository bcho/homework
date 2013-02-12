#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lifegame_constants.h"
#include "grid.h"
#include "io.h"

int init_state(struct grid_t **grid);
int count_neighbors(struct grid_t *grid, int x, int y);
void update_grid(struct grid_t *curr, struct grid_t *next);
int grid_hit_max_age(struct grid_t *grid);

int main()
{
    /* init game */
    struct grid_t *curr, *next;
    char enter;

    /* get init state */
    while (!init_state(&next))
        ;
    curr = grid_init(next->rows, next->cols);

    /* start game */
    while (1) {
        if (grid_cmp(next, curr) == 0 || grid_hit_max_age(curr)) {
            printf("game is over\n");
            break;
        }

        grid_cpy(next, curr);
        print_grid(curr, 'X', '-');
        
        /* calculate next state */
        update_grid(curr, next);

        /* block the game */
        //enter = getchar();
        sleep(1);
    }

    /* end game */
    grid_free(curr);
    grid_free(next);

    return 0;
}

int count_neighbors(struct grid_t *grid, int x, int y)
{
    int i, j, count;
    int d[3] = {-1, 0, 1};

    for (count = 0,i = 0;i < 3;i++)
        for (j = 0;j < 3;j++)
            if (!(d[i] + x >= grid->rows || d[i] + x < 0 || \
                d[j] + y >= grid->cols || d[j] + y < 0 || \
                (d[i] == 0 && d[j] == 0))) {
                count += (grid_retrieve(grid, x + d[i], y + d[j])) ? (1) : (0);
            }
    return count;
}

void update_grid(struct grid_t *curr, struct grid_t *next)
{
    int i, j, neighbors;

    for (i = 0;i < curr->rows;i++)
        for (j = 0;j < curr->cols;j++) {
            neighbors = count_neighbors(curr, i, j);
            if (neighbors == 0 || neighbors == 1)
                grid_set(next, i, j, 0);
            else if (neighbors == 2)
                grid_set(next, i, j, grid_retrieve(curr, i, j));
            else if (neighbors == 3)
                grid_set(next, i, j, grid_retrieve(curr, i, j) + 1);
            else
                grid_set(next, i, j, 0);
        }
}

int init_state(struct grid_t **grid)
{
    int choice;
    char name[20];

    printf("start from file or randomly?\n0) from file\n1) randomly\n");
    scanf("%d", &choice);

    if (choice < 0 || choice > 1)
        return 0;

    if (choice == 1) {
        *grid = init_grid_from_random();
        return 1;
    }

    if (choice == 0) {
        printf("input filename\n");
        scanf("%s", name);
        *grid = init_grid_from_file(name, lifegame_max_cols, \
                lifegame_file_comment, lifegame_file_alive,
                lifegame_file_dead);
        if (grid == NULL)
            return 0;
        return 1;
    }

    return 0;
}

int grid_hit_max_age(struct grid_t *grid)
{
    int i, current, found_alive;

    for (found_alive = 0, i = 0;i < grid->cols * grid->rows;i++) {
        current = grid_retrieve(grid, i / grid->cols, i % grid->cols);
        if (current != 0 && current < lifegame_max_age)
            return 0;
        if (current != 0)
            found_alive = 1;
    }
    return found_alive;
}
