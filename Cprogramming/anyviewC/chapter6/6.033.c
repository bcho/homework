#include <stdio.h>

int main()
{
    int a[5] = {1, 2, 3, 4, 5};
    int n = 5, max = - 2 << 29, min = 2 << 29, i, sum;
    double avg;

    for (i = 0, sum = 0;i < n;i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
        sum += a[i];
    }
    avg = (double) sum / n;

    printf("%d %d %lf", min, max, avg);

    return 0;
}
