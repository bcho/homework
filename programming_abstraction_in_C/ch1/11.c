#include <stdio.h>
#include <math.h>

#define square(x) ((x) * (x))

double area(int r, int n);

int main()
{
    int r, n;

    r = 2; n = 1000;
    printf("the area of the quarter circle (r is %d inch) "
           "by dividing it into %d rectangles is %lf",
           r, n, area(r, n));

    return 0;
}

double area(int r, int n)
{
    double ret, h, w;
    int i;

    for (i = 1, ret = 0, w = (double) r / n;i <= n;i++) {
        h = sqrt(square(r) - square(w * i - w / 2));
        ret += h * w;
    }

    return ret;
}
