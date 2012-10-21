#include <stdio.h>

int main()
{
    int a;

    a = 600;

    // don't use
    //
    //     printf("%d\n%d\n", a++, ++a);
    //
    // because it will have side effect.
    printf("%d\n", a++);
    printf("%d\n", ++a);

    return 0;
}
