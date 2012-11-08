#include <stdio.h>

#define N 3

void invert(char a[N][N]);
void invertH(char a[N][N]);
void invertV(char a[N][N]);
void turningClockwise(char a[N][N]);
void turningAnticlockwise(char a[N][N]);
void turningRight(char a[N][N]);
void turningLeft(char a[N][N]);
void print(char a[N][N]);

int main()
{
    char a[N][N] = {{1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}};

    turningLeft(a);

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

void invertV(char a[N][N])
{
    int i, j;
    char b[N][N];

    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            b[i][j] = a[i][j];
    
    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            a[i][j] = b[i][N - 1 - j];

    return;
}

void turningClockwise(char a[N][N])
{
    int i, j;
    char b[N][N];

    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            b[i][j] = a[i][j];

    for (i = 1;i < N;i++) {
        a[0][i] = b[0][i - 1];
        a[i][N - 1] = b[i - 1][N - 1];
    }
    for (i = 0;i < N - 1;i++) {
        a[N - 1][i] = b[N - 1][i + 1];
        a[i][0] = b[i + 1][0];
    }
    
    return;
}

void turningAnticlockwise(char a[N][N])
{
    int i, j;
    char b[N][N];

    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            b[i][j] = a[i][j];

    for (i = 1;i < N;i++) {
        a[N - 1][i] = b[N - 1][i - 1];
        a[i][0] = b[i - 1][0];
    }
    for (i = 0;i < N - 1;i++) {
        a[0][i] = b[0][i + 1];
        a[i][N - 1] = b[i + 1][N - 1];
    }
    
    return;
}

void turningRight(char a[N][N])
{
    int i, j;
    char b[N][N];

    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            b[i][j] = a[i][j];

    for (i = 1;i < N;i++)
        for (j = 0;j < N;j++)
            a[j][i] = b[j][i - 1];
    for (j = 0;j < N;j++)
        a[j][0] = b[j][N - 1];

    return;
}

void turningLeft(char a[N][N])
{
    int i, j;
    char b[N][N];

    for (i = 0;i < N;i++)
        for (j = 0;j < N;j++)
            b[i][j] = a[i][j];

    for (i = 0;i < N - 1;i++)
        for (j = 0;j < N;j++)
            a[j][i] = b[j][i + 1];
    for (j = 0;j < N;j++)
        a[j][N - 1] = b[j][0];

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
