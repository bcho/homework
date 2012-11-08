#include <stdio.h>

int findmax(int s[], int n);

int main()
{
    int s[5] = {5, 4, 15, 20, 1};

    printf("%d", findmax(s, 4));

    return 0;
}

int findmax(int s[], int n)
{
    int max;
    for (max = -2 << 29, n--;n >= 0;n--)
        max = (max > *(s + n)) ? max : *(s + n);

    return max;
}
