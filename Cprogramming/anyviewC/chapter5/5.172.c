#include <stdio.h>

int main()
{
    int a, n, i;
    long s, tmp;

    scanf("%d %d", &a, &n);

    for (i = 0, tmp = 0, s = 0;i < n;i++) {
        tmp = tmp * 10 + a;
        s += tmp;
    }

    printf("%ld", s);

    return 0;
}
