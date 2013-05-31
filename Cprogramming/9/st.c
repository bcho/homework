#include <stdio.h>
#include <stdlib.h>

#include "st.h"

void build(struct st **list)
{
    struct st *head, *prev, *p;
    int num;

    head = NULL;
    while (1) {
        scanf("%d", &num);

        if (num == 0)
            break;

        if ((p = malloc(sizeof(struct st))) == NULL)
            perror("malloc");
        p->num = num;
        if (head == NULL)
            head = p;
        else
            prev->s = p;
        prev = p;

    }
    *list = head;
}

void destory(struct st *list)
{
    struct st *prev;
    while (list != NULL) {
        prev = list->s;
        free(list);
        list = prev;
    }
}

void print(struct st *list)
{
    for (;list != NULL;list = list->s)
        printf("%ld ", list->num);
    printf("\n");
}
