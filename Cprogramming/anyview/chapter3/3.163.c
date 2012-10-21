#include <stdio.h>

int main()
{
    int a1, a2;
    float b, c;

    b = 34.567;
    c = 56.789;

    a1 = (int) (b * c);
    a2 = (int) b * (int) c;

    printf("a1=%d\na2=%d\n", a1, a2);

    return 0;
}
