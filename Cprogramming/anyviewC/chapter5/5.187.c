#include <stdio.h>

int main()
{
    int i, s, m, n, t, p;
    
    scanf("%d %d", &m, &n);

    for (i = 1, p = 1, t = 0;i <= n;i++, p *= 10) {
        t = p * i + t;
        if (i >= m)
            s += t;
    }

    printf("%d", s);

    return 0;
}
