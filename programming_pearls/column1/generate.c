#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bitvector.h"

#define N 10000000

int
main(int argc, char *argv[])
{
    int generated, k, p;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [count]\n", argv[0]);
        return -1;
    }
    
    srand(time(NULL));
    k = atoi(argv[argc - 1]);

    for (generated = 0;generated < k;) {
        p = random() % N;

        if (!get_vector(p)) {
            set_vector(p, 1);
            printf("%ld\n", p);
            generated++;
        }
    }

    return 0;
}
