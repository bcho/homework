#include <stdio.h>

int
main(int argc, char *argv[])
{
    int n;

    if (argc < 2) {
        return -1;
    }

    sscanf(argv[1], "%x", &n);
    printf("%d", n);

    return 0;
}
