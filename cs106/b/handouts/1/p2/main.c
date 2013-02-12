#include <stdio.h>

#include "scores.h"

#define FNAME "scores.in"

int main()
{
    struct scores_statistics *stat;

    stat = read_scores(FNAME);

    printf("max:\t\t%.3lf\nmin:\t\t%.3lf\naverage:\t%.3lf\n", stat->max,
            stat->min, stat->average);

    free_scores(stat);

    return 0;
}
