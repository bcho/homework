#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SN 100
#define MAX_LN 100
#define MAX_CH 81

typedef char *line_t;
typedef line_t *segment_t;

void insert(segment_t *s, int seg_c, int line_c);

int main()
{
    int sn, ln, i, j, scen_count;
    segment_t cur;
    char c;

    scanf("%d %d\n", &sn, &ln);
    scen_count = 0;
    while (sn != 0 || ln !=0) {

        /* read segments */
        segment_t *segs = malloc(sizeof(segment_t) * sn);
        for (i = 0;i < sn;i++) {
            segs[i] = malloc(sizeof(line_t) * ln);
            for (cur = segs[i], j = 0;j < ln;j++) {
                cur[j] = malloc(sizeof(char) * MAX_CH);
                /* FIXME how to read the entire line? */
                fgets(cur[j], MAX_CH, stdin);
            }
        }

        /* sort poems with O(n^2) */
        insert(segs, sn, ln);

        /* print segments */
        printf("Scenario#%d\n", ++scen_count);
        for (i = 0;i < sn;i++) {
            for (cur = segs[i], j = 0;j < ((i == sn - 1) ? (ln) : (ln - 1));
                 j++)
                printf("%s", cur[j]);
        }

        /* free segments */
        for (i = 0;i < sn;i++) {
            for (cur = segs[i], j = 0;j < ln;j++) {
                free(cur[j]);
            }
            free(cur);
        }
        free(segs);

        
        /* read next group */
        scanf("%d %d\n", &sn, &ln);
    }

    return 0;
}

void insert(segment_t s[], int seg_c, int line_c)
{
    int last, j, k;
    line_t front, rear;
    segment_t cur, tmp;

    for (last = 0;last < seg_c - 1;) {
        front = s[0][0];
        rear = s[last][line_c - 1];

        for (j = last + 1;j < seg_c;) {
            cur = s[j];
            if (strcmp(cur[line_c - 1], front) == 0) {
                for (k = j;k > 0;k--)
                    s[j] = s[j - 1];
                s[0] = cur;
                last++;
                j = last;
            } else if (strcmp(cur[0], rear) == 0 && last < seg_c - 1) {
                tmp = s[++last];
                s[last] = s[j];
                s[j] = tmp;
                j = last;
            } else {
                j++;
            }
        }
    }
}
