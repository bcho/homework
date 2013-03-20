#include <stdio.h>
#include <stdlib.h>

#define RANGE 10

int read_mark(int **marks);
void horizontal_print(int count, int *marks);
void vertical_print(int count, int *marks);

int main() {
    int *marks;
    int count;

    count = read_mark(&marks);
    vertical_print(count, marks);
    horizontal_print(count, marks);

    free(marks);

    return 0;
}


int read_mark(int **marks)
{
    int current, count;

    for (current = 0, count = 0;current != -1;) {
        if (count) {
            if (current <= RANGE * 10 && current >= 0) {
                *(*marks + count - 1) = current;
                *marks = realloc(*marks, sizeof(int) * (count + 1));
                count += 1;
            } else {
                printf("input illegal!\n");
            }
        } else {
            *marks = malloc(sizeof(int) * (count + 1));
            count += 1;
        }
        scanf("%d", &current);
    }

    return count - 1;
}

void vertical_print(int count, int *marks)
{
    int range[RANGE + 1];
    int i, j, max;
    char aster;

    for (i = 0;i <= RANGE;i++) {
        range[i] = 0;
    }

    for (i = 0, max = -1;i < count;i++) {
        range[marks[i] / RANGE] += 1;
        if (max < range[marks[i] / RANGE])
            max = range[marks[i] / RANGE];
    }

    for (i = 0;i < max;i++) {
        for (j = 0;j <= RANGE;j++) {
            if (range[j] - (max - i) >= 0) {
                aster = '*';
                range[j] -= 1;
            } else {
                aster = ' ';
            }
            printf("  %c", aster);
        }
        printf("\n");
    }
    for (i = 0;i <= RANGE;i++)
        printf(" %2d", i * RANGE);
    printf("\n");
}

void horizontal_print(int count, int *marks) {
    int range[RANGE + 1];
    int i, j;

    for (i = 0;i <= RANGE;i++) {
        range[i] = 0;
    }

    for (i = 0;i < count;i++)
        range[marks[i] / RANGE] += 1;

    for (i = 0;i <= RANGE;i++) {
        printf("%3d: ", i * RANGE);
        for (j = 0;j < range[i];j++)
            printf("*");
        printf("\n");
    }
}
