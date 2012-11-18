#include <stdio.h>
#include <stdlib.h>
#include "time_measure.h"
#include "search.h"

int main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("You should specify length and ticks!\n");
        return 0;
    }

    int count = (int) strtol(argv[1], NULL, 10);
    int ticks = (int) strtol(argv[2], NULL, 10);
    double d;

    printf("Search %d elements list with %d times:\n", count, ticks);
    char report[] = "%s:\n\ttotal %lfs\tduration %lfs\n";

    /* sequential */
    d = duration(sequential, count ,ticks);
    printf(report, "Sequential", d, d / ticks);

    /* iterative binary search */
    d = duration(ibinary, count, ticks);
    printf(report, "Iterative binary search", d, d / ticks);

    /* recursive binary search */
    d = duration(rbinary, count, ticks);
    printf(report, "Recursive binary search", d, d / ticks);

    return 0;
}
