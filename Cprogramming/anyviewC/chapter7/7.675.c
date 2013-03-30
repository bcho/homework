#include <stdio.h>

void func(int s[], int n, int p[]);

int main()
{
    int n = 5;
    int s[5] = {50, 65, 75, 85, 95};
    int p[5];

    func(s, n, p);
    for (n = 0;n < 5;n++)
        printf("%d ", p[n]);

    return 0;
}

void func(int s[], int n, int p[])
{
    int i;
    
    for (i = 0;i < 5;i++)
        p[i] = 0;

    for (n = n - 1;n >= 0;n--)
        switch (s[n] / 10) {
            case 9: p[4]++; break;
            case 8: p[3]++; break;
            case 7: p[2]++; break;
            case 6: p[1]++; break;
            default: p[0]++;
        }
}
