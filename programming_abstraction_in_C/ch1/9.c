#include <stdio.h>

int Round(double x);

int main()
{
    double x;

    printf("input x: ");
    scanf("%lf", &x);
    printf("the nearest integer of %lf is %d", x, Round(x));

    return 0;
}

int Round(double x)
{
    return (int) (x + 0.5);
}
