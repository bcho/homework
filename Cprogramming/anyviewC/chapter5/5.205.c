#include <stdio.h>

int main()
{
    int i;
    for (i = 100;i <= 200;i++) {
        if ((i % 7 == 4) && (i % 4 == 2) && (i % 9 == 5)) {
            printf("total: %d", i);
            break;
        }
    }

    return 0;
}
