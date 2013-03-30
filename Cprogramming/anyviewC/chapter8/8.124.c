#include <stdio.h>

int min3adj(int s[], int n);

int main()
{
    int n = 5;
    int s[5] = {10, 2, 3, 4, 5};

    printf("%d", min3adj(s, n));

    return 0;
}

int min3adj(int s[], int n)
{
    int i, min, cur;

    for (i = 1, min = 2 << 15;i < n - 1;i++) {
        cur = s[i] + s[i - 1] + s[i + 1];
        if (cur < min)
            min = cur;
    }

    return min;
}
