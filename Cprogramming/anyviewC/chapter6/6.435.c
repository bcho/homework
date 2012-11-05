#include <stdio.h>

int main()
{
    int a[150], b[150], n = 15, i, sum, t, j;

    for (i = 0, t = 2, j = 1;i < n;i++, t += 2, j++) {
        a[i] = t;
        sum += t;
        if (j % 5 == 0) {
            b[j / 5 - 1] = sum / 5;
            printf("%d ", b[j / 5 - 1]);
            sum = 0;
        }
    }

    printf("\n");
    for (i = 0;i < n;i++)
        printf("%d ", a[i]);

    return 0;
}
