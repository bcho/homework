#include <stdio.h>

int main()
{
    int x, y, z, i, result = 532;

    for (i = 100;i <= 999;i++) {
        x = i / 100;
        y = i / 10 % 10;
        z = i % 10;

        if (110 * y + 100 * x + 12 * z == result)
            printf("x=%d,y=%d,z=%d\n", x, y, z);
    }

    return 0;
}
