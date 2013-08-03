#include <stdio.h>

#define GUEST 0x87654321

#define PRT(x) printf("0x%08X\n", (x))

int
main()
{
    // A
    PRT(GUEST & 0xFF);

    // B
    PRT(~(0xFF | GUEST) | (GUEST & 0xFF));

    // C
    PRT(0xFF | GUEST);

    return 0;
}
