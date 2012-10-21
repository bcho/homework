#include <stdio.h>

int main()
{
    int m, n, s;

    scanf("%d", &m);

    n = 1;
    s = 0;
    while (s < m) {
        s += n;
        if (s < m) n++;
    }
    s -= n--;

    printf("%d %d", s, n);

    return 0;
}
