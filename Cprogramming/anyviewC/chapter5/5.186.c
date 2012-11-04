#include <stdio.h>

int main()
{
    int i, s, m, n, t;
    
    scanf("%d %d", &m, &n);

    for (i = 1, t = 0;i <= m;i++) t = t * 10 + i;
    for (i = m, s = 0;i <= n;i++, t = t * 10 + i) s += t;

    printf("%d", s);

    return 0;
}
