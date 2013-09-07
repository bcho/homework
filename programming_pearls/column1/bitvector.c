#include "assert.h"

#define N 10000000
#define BITSCOUNT (N / 32)

unsigned int vector[BITSCOUNT];

void
init_vector()
{
    int i;

    for (i = 0;i < BITSCOUNT;i++)
        vector[i] = 0;
}

void
set_vector(int i, unsigned int p)
{
    int x, y;

    assert(p == 0u || p == 1u);
    assert(i < N);

    x = i / 32;
    y = (i - x) % 32;

    vector[x] |= (1u & p) << y;
}

unsigned int
get_vector(int i)
{
    int x, y;

    assert(i < N);

    x = i / 32;
    y = (i - x) % 32;

    return (vector[x] >> y) & 1u;
}

unsigned int
get_vector_block(int i)
{
    return vector[i];
}
