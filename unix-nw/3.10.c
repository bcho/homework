/*
 * figure 3.10
 *
 * Check host byte order.
 */

#include <stdio.h>

int
main()
{
    union {
        short s;
        char c[sizeof(short)];
    } un;

    un.s = 0x0102;
    /*
     * bit field:
     *  0000 0001 0000 0010
     *
     * little endian:
     *  0000 0010 0000 0001
     *          ^         ^
     *          2         1
     *        c[0]      c[1]
     *
     * big endian: (和自然书写方向一致)
     *  0000 0001 0000 0010
     *          ^         ^
     *          1         2
     *        c[0]      c[1]
     */
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2)
           printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("little-endian\n");
        else
            printf("unknown");
    } else {
        printf("sizeof(short) = %d\n", sizeof(short));
    }

    return 0;
}
