#include <stdio.h>
#include <stdlib.h>

#include "scores.h"

#define T struct scores_statistics
#define MAXINT 2 << 15

T *read_scores(char *fname)
{
    T *ret;
    FILE *stream;
    double score;

    ret = malloc(sizeof(T));
    ret->max = - (MAXINT);
    ret->min = (MAXINT);
    stream = fopen(fname, "r");
    for (ret->size = 0;(fscanf(stream, "%lf", &score) != EOF);ret->size++) {
        ret->total += score;
        ret->max = (score > ret->max) ? (score) : (ret->max);
        ret->min = (score < ret->min) ? (score) : (ret->min);
    }
    ret->average = ret->total / ret->size;
    fclose(stream);

    return ret;
}

void free_scores(T *stat)
{
    free(stat);
}
