#include <stdio.h>

int main()
{
    int n;
    // do you mean double?
    double s;

    scanf("%d", &n);

    s = 0;
    while (n)
        s += 1 / (double) n--;

    printf("%lf", s);

    return 0;
}
