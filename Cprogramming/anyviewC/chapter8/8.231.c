#include <stdio.h>

void func(char *s, int i, int n, char *t)
{
    int j;

    for (j = n, s = s + i - 1;(j--) && (*t++ = *s++);)
        ;
    t[n] = 0;
}

int main()
{
    char t[20];

    func("I am a student.", 8, 7, t);
    printf("%s", t);

    return 0;
}
