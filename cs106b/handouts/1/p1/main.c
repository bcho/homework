#include <stdio.h>

#include "censor_string.h"

int main()
{
    char text[1000], remove[1000];

    fgets(text, 1000, stdin);
    fgets(remove, 1000, stdin);

    printf("%s\n", CensorString(text, remove));

    return 0;
}
