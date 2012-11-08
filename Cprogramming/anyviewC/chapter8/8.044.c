#include <stdio.h>

long func(char *s);

int main()
{
    printf("%ld", func("adjfklj123-9-9jaldf-0123kjj"));

    return 0;
}

long func(char *s)
{
    long ret;

    for (ret = 0;*s;s++)
        if (*s >= '0' && *s <= '9')
            ret = ret * 10 + (*s - '0');

    return ret;
}
