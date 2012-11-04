#include <stdio.h>

int main()
{
    int term, result;
    char ch;

    scanf("%d", &result);
    ch = getchar();
    while (ch != ';') {
        scanf("%d", &term);
        if (ch == '*') result *= term;
        if (ch == '/') result /= term;
        ch = getchar();
    }

    printf("result: %d\n", result);

    return 0;
}
