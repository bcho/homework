#include <stdio.h>

int main()
{
    int a;
    float b, c;

    b = 2.34567;
    c = 56.789;
    a = (int) b + (int) c;

    printf("a=%d\n", a);

    return 0;
}
