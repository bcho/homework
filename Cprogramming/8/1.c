#include <stdio.h>

#define N 3

void _swap(int *p1, int *p2);
void swap(int *p1, int *p2, int n);
void swap_rows(int a, int b, int square[][N]);
void print(int a[][N]);

int main()
{
    int a[N][N] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    print(a);
    swap_rows(1, 2, a);
    print(a);
    swap(a[1], a[2], N);
    print(a);

    return 0;
}

void print(int a[][N])
{
    int i, j;

    for (i = 0;i < N;i++) {
        for (j = 0;j < N;j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

inline void _swap(int *p1, int *p2)
{
    int temp;

    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void swap(int *p1, int *p2, int n)
{
    int i;

    for (i = 0;i < n;i++)
        _swap(&p1[i], &p2[i]);
}

void swap_rows(int a, int b, int square[][N])
{
    int i;

    for (i = 0;i < N;i++)
        _swap(&square[a][i], &square[b][i]);
}
