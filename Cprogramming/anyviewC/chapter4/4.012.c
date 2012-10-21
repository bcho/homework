#include <stdio.h>

int main()
{
    int a, a1;

    scanf("%d", &a);

    a1 = a < 0 ? -a : a;

    printf("|%d| = %d\n", a, a1);

    return 0;
}
