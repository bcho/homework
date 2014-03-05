#include <assert.h>

enum result {
    OK,
    FAIL
};

#define MAXCAP (1 << 10)

/*
 * Calculate the m-th item in the k-fibonacci sequence.
 *
 * Defination:
 *
 *  0 .. k - 2 = 0
 *       k - 1 = 1
 *           k = SUM(0 .. k - 1)
 *       k + 1 = SUM(1 .. k + 1)
 *            ...
 */
enum result kfibonacci(int k, int m, int *rv)
{
    // Perform fesibility checks first.
    if (!(k > 1 && m >= 0))
        goto fail;
    if (k > MAXCAP)
        goto fail;

    // Some simple cases.
    // 0 .. k - 2 is 0.
    if (m < k - 1) {
        *rv = 0;
        goto exit_early;
    }
    // k, k + 1 is 1.
    if (m < k + 1) {
        *rv = 1;
        goto exit_early;
    }

    // Use a cyclic queue.
    // Maybe use unsigned to extend the range?
    int queue[MAXCAP];
    int counter, sum, index, pop;

    // Initial the queue.
    for (counter = 0; counter < k - 1; counter++)
        queue[counter] = 0;
    queue[k - 1] = 1;
    sum = queue[k - 1];

    while (counter < m) {
        // Pop the oldest number.
        index = counter % k;
        pop = queue[index];
        queue[index] = sum;

        // Next number.
        sum = sum - pop + queue[index];
        if (sum < 0)
            goto fail;

        counter = counter + 1;
    }

    *rv = sum;

    return OK;

fail:
    *rv = 0;
    return FAIL;
exit_early:
    return OK;
}

int main()
{
    int result;

    assert(FAIL == kfibonacci(2, -1, &result));
    assert(FAIL == kfibonacci((2 << 11), (2 << 11), &result));
    assert(FAIL == kfibonacci(2, (2 << 10), &result));

    assert(OK == kfibonacci(2, 3, &result));
    assert(2 == result);
    
    assert(OK == kfibonacci(2, 1, &result));
    assert(1 == result);
    
    assert(OK == kfibonacci(2, 0, &result));
    assert(0 == result);

    assert(OK == kfibonacci(3, 4, &result));
    assert(2 == result);
    
    assert(OK == kfibonacci(3, 5, &result));
    assert(4 == result);
    
    assert(OK == kfibonacci(3, 6, &result));
    assert(7 == result);
    
    assert(OK == kfibonacci(3, 7, &result));
    assert(13 == result);

    return 0;
}
