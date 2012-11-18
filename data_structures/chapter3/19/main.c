#include <stdio.h>
#include "postfix.h"

int main()
{
    char f[MAX_OP], c;
    int i;

    for (i = 0;(c = getchar()) != EOF;f[i++] = c)
        ;
    printf("%d", evaluate(f));
    return 0;
}
