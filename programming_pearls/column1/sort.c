#include <stdio.h>
#include <stdlib.h>
#include "assert.h"

#include "bitvector.h"
#include "usage.h"

#define N 1000000

int
main(int argc, char *argv[])
{
    FILE *f;
    char *num;
    int i;
    size_t length;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [input]", argv[0]);
        return -1;
    }

    f = fopen(argv[argc - 1], "r");
    num = NULL;
    while (getline(&num, &length, f) != -1) {
        i = atoi(num);
        assert(!get_vector(i));
        set_vector(i, 1);
        free(num);
        num = NULL;
    }
    fclose(f);
    for (i = 0;i < N;i++)
        if (get_vector(i))
            printf("%d\n", i);

    get_usage();
    scanf("%d", &i);

    return 0;
}
