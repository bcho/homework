#include <stdio.h>

void func(char s[], int n);

int main()
{
    char s[] = "****A*BCDE**F*******";

    func(s, 8);
    printf("%s", s);

    return 0;
}

void func(char s[], int n)
{
    char *tail;

    for (tail = s;*tail;tail++)
        ;
    if (*(tail - n) != '*')
        return;
    for (;*(tail - n) == '*';tail--)
        ;
    *(tail + 1) = 0;
}
