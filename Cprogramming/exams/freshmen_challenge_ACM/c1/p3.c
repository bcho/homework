#include <stdio.h>

#define MAX 50

void print_matrix(int n);

int main()
{
    int n;
    scanf("%d", &n);

    print_matrix(n);

    return 0;
}

void print_matrix(int n)
{
    int matrix[MAX + 2][MAX + 2];
    int x, y, dirx, diry, count;

    for (x = 0;x <= n+1;x++)
        for (y = 0;y <= n+1;y++)
            matrix[x][y] = 1;
    for (x = 1;x <= n;x++)
        for (y = 1;y <= n;y++)
            matrix[x][y] = -1;

    dirx = 0, diry = 1;
    x = 1, y = 0;
    for (count = 1;count <= n*n;count++) {
        if (matrix[x + dirx][y + diry] != -1) {
            if (dirx == 0 && diry == 1)
                dirx = 1, diry = 0;
            else if (dirx == 1 && diry == 0)
                dirx = 0, diry = -1;
            else if (dirx == 0 && diry == -1)
                dirx = -1, diry = 0;
            else if (dirx == -1 && diry == 0)
                dirx = 0, diry = 1;
        }
        x += dirx;
        y += diry;
        matrix[x][y] = count;
    }

    for (x = 1;x <=n;x++) {
        for (y = 1;y < n;y++)
            printf("%d ", matrix[x][y]);
        printf("%d\n", matrix[x][n]);
    }
}
