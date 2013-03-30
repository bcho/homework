#include <stdio.h>

#define lower(a) (((a) <= 'Z' && (a) >= 'A') ? ((a) - 'A' + 'a') : (a))

char s[] = "hELLowORlD";
int n = 10;

int main()
{
    char *c;

    for (c = s;*c;c++)
        *c = lower(*c);

    printf("%s", s);

    return 0;
}
