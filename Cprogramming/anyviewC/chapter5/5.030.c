#include <stdio.h>

int main()
{
    int n = 15;
    long f;

    f = 1;
    while (n)
        f *= n--;

    printf("%ld", f);

    return 0;
}
