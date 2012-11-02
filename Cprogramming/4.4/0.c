#include <stdio.h>

#define max(a, b) ((a) > (b)) ? (a) : (b)

int main()
{
    int a, b, c, m;

    scanf("%d %d %d", &a, &b, &c);

    m = a;
    m = max(m, b);
    m = max(m, c);

    printf("%d", m);

    return 0;
}
