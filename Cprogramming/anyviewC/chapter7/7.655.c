#include <stdio.h>

void func(char *s, int *num);

int main()
{
    char s[] = "THIs is a book";
    int i;
    int num[5];


    func(s, num);
    for (i = 0;i < 5;i++)
        printf("%d ", num[i]);

    return 0;
}

#define lower(a) (((a) <= 'Z' && (a) >= 'A') ? ((a) - 'A' + 'a') : (a))

void func(char *s, int *num)
{
    int i;
    char *c;

    for (i = 0;i < 5;i++)
        num[i] = 0;
    for (c = s;*c;c++)
        if (lower(*c) == 'a')
            num[0]++;
        else if (lower(*c) == 'e')
            num[1]++;
        else if (lower(*c) == 'i')
            num[2]++;
        else if (lower(*c) == 'o')
            num[3]++;
        else if (lower(*c) == 'u')
            num[4]++;
}
