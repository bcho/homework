#include <stdio.h>

void func(char *s, char *t);

int main()
{
    char s[] = "time", t[100];

    func(s, t);

    printf("%s", t);

    return 0;
}

void func(char *s, char *t)
{
    while (*(++s))
        ;
    s--;
    while ((*(t++) = *(s--)))
        ;

    return;
}
