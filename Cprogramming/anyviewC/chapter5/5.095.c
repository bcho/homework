#include <stdio.h>

int main()
{
    int n; 
    double t, denom, numer, s;

    scanf("%d", &n);
    
    denom = 2, numer = 1;
    s = 0;
    while (n--) {
        s += denom / numer;
        t = denom;
        denom += numer;
        numer = t;
    }

    printf("%lf", s);

    return 0;
}
