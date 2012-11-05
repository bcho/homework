#include <stdio.h>

#define MAX 1000

int main()
{
    int n = 3, i, j, is_found;
    int a[3][3] = {{12, 22, 3}, {3, 4, 5}, {1, 7, 9}};
    int lx[MAX], ly[MAX], rx[MAX], ry[MAX];

    is_found = 0;
    for (i = 0;i < n;i++) {
        lx[i] = i, ly[i] = 0;
        rx[i] = 0, ry[i] = i;
        for (j = 0;j < n;j++) {
            if (a[i][j] > a[lx[i]][ly[i]])
                ly[i] = j;
            if (a[j][i] < a[rx[i]][ry[i]])
                rx[i] = j;
        }
        if (lx[i] == rx[i] && ly[i] == ry[i]) {
            printf("(%d, %d) => %d\n", lx[i], ly[i], a[lx[i]][ly[i]]);
            is_found = 1;
        }
    }

    if (!is_found)
        printf("Not found!");

    return 0;
}
