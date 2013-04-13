#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void int2string_aux(int n, char s[], int t, int l);
char *int2string(int n);

int main()
{
    int n;
    char *str;

    scanf("%d", &n);
    str = int2string(n);
    printf("%s", str);
    free(str);

    return 0;
}

void int2string_aux(int n, char s[], int t, int l)
{
    s[l] = n % 10 + '0';
    if (l != t)
        int2string_aux(n / 10, s, t, l - 1);
}

char *int2string(int n)
{
    int length, sign;
    char *str;

    sign = 1;
    if (n < 0) {
        sign *= -1;
        n *= -1;
    }
    if (n != 0)
        length = (int) (log(n) / log(10)) + 1 + ((sign == -1) ? 1 : 0);
    else
        length = 1;
    str = malloc(sizeof(char) * length);
    if (sign == 1) {
        int2string_aux(n, str, 0, length - 1);
    } else if (sign == -1) {
        str[0] = '-';
        int2string_aux(n, str, 1, length - 1);
    }
    str[length] = 0;

    return str;
}
