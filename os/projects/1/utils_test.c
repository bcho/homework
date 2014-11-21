#include "lib/miniunit.h"
#include <stdlib.h>
#include <time.h>

#include "utils.h"

int tests_run;

char *
test_make_mean_seq()
{
    int i;
    int n = 100;
    double seq[n];

    make_mean_seq(n, seq);
    for (i = 0; i < n; i++)
        mu_assert("make_mean_seq", seq[i] == n);

    return 0;
}

char *
test_make_increment_seq()
{
    int n = 100;
    double seq[n];

    make_increment_seq(n, seq);
    for (n = n - 1; n > 0; n--)
        mu_assert("make_increment_seq", seq[n] > seq[n - 1]);

    return 0;
}

char *
test_make_normal_distribution_seq()
{
    int n = 100;
    double seq[n];

    srand(time(NULL));

    make_normal_distribution_seq(n, seq);
    for (n = n - 1; n > 2; n -= 2)
        // mu_assert("make_normal_distribution_seq", seq[n] == -seq[n - 1]);
        // printf("%f %f\n", seq[99], seq[98]);
        ;

    return 0;
}

char *
run()
{
    mu_run_test(test_make_mean_seq);
    mu_run_test(test_make_increment_seq);
    mu_run_test(test_make_normal_distribution_seq);

    return 0;
}

TEST_MAIN;
