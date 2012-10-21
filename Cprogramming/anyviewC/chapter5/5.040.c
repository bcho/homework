#include <stdio.h>

int main()
{
    int m, n, s;

    scanf("%d", &m);

    s = 0;
    n = 1;
    while (s < m)
        s += n++;
    n--;

    printf("%d %d", n, s);

    return 0;
}
