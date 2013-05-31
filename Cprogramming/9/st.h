#ifndef ST_H
#define ST_H

struct st {
    long num;
    char name[12];
    float score;

    struct st *s;
};

void build(struct st **list);
void destory(struct st *list);
void print(struct st *list);

#endif
