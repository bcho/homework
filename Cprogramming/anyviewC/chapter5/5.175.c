#include <stdio.h>

int main()
{
    int a, m, n, i;
    long s, tmp;

    scanf("%d %d %d", &a, &m, &n);

    for (i = 1, tmp = 0;i < m;i++)
        tmp = tmp * 10 + a;
    for (i = m, s = 0;i <= n;i++) {
        tmp = tmp * 10 + a;
        s += tmp;
    }

    printf("%ld", s);

    return 0;
}
