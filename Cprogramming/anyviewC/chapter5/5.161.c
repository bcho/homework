#include <stdio.h>

int main()
{
    int i, n, s, tmp;

    scanf("%d", &n);

    tmp = 1;
    for (i = 1, s = 0;i <= n;i++) {
        tmp *= i;
        s += tmp;
    }

    printf("%d", s);

    return 0;
}
