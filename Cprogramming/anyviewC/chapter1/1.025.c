#include <stdio.h>

int main()
{
    int i;
    char delim = '*';

    for (i = 0;i < 20;i++)
        printf("%c", delim);

    printf("\n%c    Very Good!    %c\n", delim, delim);

    for (i = 0;i < 20;i++)
        printf("%c", delim);

    return 0;
}
