#include <stdio.h>

long func(char *s);

int main()
{
    printf("%ld", func("--123"));

    return 0;
}

long func(char *s)
{
    int minus;
    long ret;

    for (minus = 1;!(*s >= '0' && *s <= '9');s++)
        if (*s == '-')
            minus *= -1;
    for (ret = 0;*s;s++)
        if (*s >= '0' && *s <= '9')
            ret = ret * 10 + (*s - '0');

    return ret * minus;
}
