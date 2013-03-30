#include <stdio.h>

int func(char a[]);

int main()
{
    char a[] = "ABCD";

    printf("%d ", func(a));
    printf("%s", a);

    return 0;
}

int func(char a[])
{
    int i, count;

    if (!a[0])
        return 0;
    for (i = 1, count = 1;a[i];i++)
        if (a[i] != a[i - 1])
            a[count++] = a[i];
    a[count] = 0;
    
    return count;
}
