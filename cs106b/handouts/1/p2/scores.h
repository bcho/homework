#ifndef SCORES_H
#define SCORES_H

#define T struct scores_statistics

struct scores_statistics {
    double max, min, average, total;
    int size;
};

T *read_scores(char *fname);
void free_scores(T *stat);

#undef T
#endif
