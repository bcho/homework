/* using reduce */

#include <stdio.h>

typedef int reduce_return_t;
typedef int reduce_func_t(int a, int b);

reduce_return_t reduce(reduce_func_t func, int seq[], int length);
reduce_func_t max;

int main()
{
    int m, seq[3];

    scanf("%d %d %d", &seq[0], &seq[1], &seq[2]);
    m = reduce(max, seq, 3);
    printf("%d", m);

    return 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

reduce_return_t reduce(reduce_func_t func, int seq[], int length)
{
    int i, r;

    if (length < 2)
        return seq[length - 1];
    
    for (i = 1, r = seq[0];i < length;i++)
        r = func(r, seq[i]);

    return r;
}
