#include <time.h>
#include "time_measure.h"

double duration(void (*func)(int), int length, int times)
{
    int i;
    clock_t start, stop;
    double d;

    start = clock();
    for (i = 0;i < times;i++)
        func(length);
    stop = clock();
    d = ((double) (stop - start)) / CLOCKS_PER_SEC;

    return d;
}
