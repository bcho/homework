#include <stdio.h>

float func(float r);

int main()
{
    float r;

    scanf("%f", &r);
    printf("%f", func(r));

    return 0;
}

float func(float r)
{
    int leap;

    leap = 0;
    if ((int) (r * 1000) % 10 >= 5)
        leap = 1;
    return (float) ((int) (r * 100) + leap) / 100;
}
