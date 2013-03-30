#include <stdio.h>

void func(char *s, int n, char *t)
{
    int len, i;
    char *c;

    for (len = 0, c = s;*c;c++, len++)
        ;
    for (c = s + len - n, i = 0;*c;c++, i++)
        *(t + i) = *c;
    t[n] = 0;
}

int main()
{
    char t[9];
    
    func("I am a student.", 4, t);
    printf("%s", t);

    return 0;
}
