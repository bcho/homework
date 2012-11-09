#include <stdio.h>

int change(int n);

int main()
{
    printf("%d", change(10));

    return 0;
}

int change(int n)
{
    int ret, times[3] = {n / 10, n / 5, n / 1}, i, j, k;

    if (!n) return 0;

    // I have no idea about how to solve it quicker...
    // so, why not search every solutions...
    // it only takes O(n^3 / 50).
    // yeah, you may say it's not a fast algorithm,
    // but I think the data is small (most are smaller than 100),
    // so we may get O(n^2) ...
    for (ret = 0, i = 0;i <= times[0];i++) {
        for (j = 0;j <= times[1];j++) {
            for (k = 0;k <= times[2];k++)
                if (i * 10 + j * 5 + k * 1 == n)
                    ret++;
        }
    }

    return ret;
}
