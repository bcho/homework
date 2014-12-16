#include "lib/miniunit.h"

#include "mem_dev.h"
#include "fs.h"
#include "config.h"

int tests_run;

char *
test_mem_dev()
{
    struct super_block *sb;

    mem_dev_init(MEM_FS_SIZE);

    sb = (struct super_block *) mem_dev_read(0);

    mu_assert("super block size", sb->size == MEM_FS_SIZE);

    mem_dev_free((unsigned char *) sb);

    return 0;
}

char *
run()
{
    mu_run_test(test_mem_dev);

    return 0;
}

TEST_MAIN;
