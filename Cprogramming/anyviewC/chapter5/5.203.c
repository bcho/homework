#include <stdio.h>

int main()
{
    int x, y, heads = 30, feet = 90;

    y = (feet - heads * 2) / 2;
    x = heads - y;

    printf("%d %d", x, y);

    return 0;
}
