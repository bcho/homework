#include <stdio.h>

#define N 3

void invert(char a[N][N]);
void invertH(char a[N][N]);
void print(char a[N][N]);

int main()
{
    char a[N][N] = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};
    invertH(a);

    print(a);

    return 0;
}

void invert(char a[N][N])
{
    int i, j;
    char b[N][N];

    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            b[i][j] = a[i][j];
    
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            a[i][j] = b[N - 1 - j][N - 1 - i];

    return;
}

void invertH(char a[N][N])
{
    int i, j;
    char b[N][N];

    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            b[i][j] = a[i][j];
    
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            a[i][j] = b[N - 1 - i][j];

    return;
}


void print(char a[N][N])
{
    int i, j;
    
    for (i = 0;i < N;i++) {
        for (j = 0;j < N;j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    return ;
}
