#include "lib/miniunit.h"
#include <string.h>

#include "fs.h"
#include "config.h"

int tests_run;

struct user test_user = {
    1,
    "test_user"
};

char *
test_entry_create_file()
{
    struct entry *file;

    file = entry_create_file("test", &test_user, PERM_RD | PERM_WR, PERM_RD);

    mu_assert("entry_create_file", file != NULL);
    mu_assert("file type", file->type == TYPE_FILE);
    mu_assert("file owner", file->owner_id == test_user.id);
    mu_assert("file owner perm", file->owner_perm == PERM_RD | PERM_WR);
    mu_assert("file other perm", file->other_perm == PERM_RD);

    mu_assert("file parent", file->parent == NULL);
    mu_assert("file content", file->content == NULL);
    
    entry_destroy(file);

    return 0;
}

char *
test_entry_create_dir()
{
    struct entry *dir;

    dir = entry_create_dir("test", &test_user, PERM_RD | PERM_WR, PERM_RD);

    mu_assert("entry_create_dir", dir != NULL);
    mu_assert("dir type", dir->type == TYPE_DIR);
    mu_assert("dir owner", dir->owner_id == test_user.id);
    mu_assert("dir owner perm", dir->owner_perm == PERM_RD | PERM_WR);
    mu_assert("dir other perm", dir->other_perm == PERM_RD);

    mu_assert("dir parent", dir->parent == NULL);
    mu_assert("dir files", dir->count == 0);

    entry_destroy(dir);

    return 0;
}

char *
test_entry_add_to_dir()
{
    struct entry *d, *f;

    f = entry_create_file("test file", &test_user, PERM_RD | PERM_WR, PERM_RD);
    d = entry_create_dir("test dir", &test_user, PERM_RD | PERM_WR, PERM_RD);

    mu_assert("entry_add_to_dir should return invalid type",
              entry_add_to_dir(f, d) == - E_INVALID_TYPE);
    mu_assert("entry_add_to_dir rv", entry_add_to_dir(d, f) == 0);
    mu_assert("entry_add_to_dir parent", f->parent == d);
    mu_assert("entry_add_to_dir count", d->count == 1);

    return 0;
}

char *
test_entry_add_to_dir_with_too_many_files()
{
    int i;
    struct entry *d, *f;

    d = entry_create_dir("test dir", &test_user, PERM_RD | PERM_WR, PERM_RD);
    for (i = 0; i < MAX_FILES; i++) {
        f = entry_create_file("test file", &test_user, PERM_RD, PERM_RD);

        entry_add_to_dir(d, f);
    }

    f = entry_create_file("test file", &test_user, PERM_RD, PERM_RD);
    mu_assert("entry_add_to_dir should return too many files",
              entry_add_to_dir(d, f) == - E_TOO_MANY_FILES);

    entry_remove(d);
    entry_remove(f);

    return 0;
}

char *
test_entry_add_to_dir_recursivly()
{
    struct entry *d1, *d2;
    
    d1 = entry_create_dir("test dir", &test_user, PERM_RD | PERM_WR, PERM_RD);
    d2 = entry_create_dir("test dir", &test_user, PERM_RD | PERM_WR, PERM_RD);

    entry_add_to_dir(d1, d2);
    mu_assert("entry_add_to_dir should return invalid type",
              entry_add_to_dir(d2, d1) == - E_INVALID_TYPE);
    
    entry_remove(d1);

    return 0;
}

char *
test_entry_rw_file()
{
    char buf[100];
    char *test_content = "foobar";
    struct entry *f;
    
    f = entry_create_file("test file", &test_user, PERM_RD | PERM_WR, PERM_RD);

    mu_assert("entry_write_file: rv", entry_write_file(f, test_content) == 6);
    mu_assert("entry_read_file: rv", entry_read_file(f, buf) == 6);
    mu_assert("entry content", strcmp(buf, test_content) == 0);

    entry_remove(f);

    return 0;
}

char *
test_entry_rw_file_with_invalid_type()
{
    char buf[100];
    struct entry *d;

    d = entry_create_dir("test dir", &test_user, PERM_RD | PERM_WR, PERM_RD);
    mu_assert("entry_write_file: rv",
              entry_write_file(d, "t") == - E_INVALID_TYPE);
    mu_assert("entry_read_file: rv",
              entry_read_file(d, buf) == - E_INVALID_TYPE);

    entry_remove(d);
    
    return 0;
}

char *
run()
{
    mu_run_test(test_entry_create_file);
    mu_run_test(test_entry_create_dir);
    mu_run_test(test_entry_add_to_dir);
    mu_run_test(test_entry_add_to_dir_with_too_many_files);
    mu_run_test(test_entry_add_to_dir_recursivly);
    mu_run_test(test_entry_rw_file);
    mu_run_test(test_entry_rw_file_with_invalid_type);

    return 0;
}

TEST_MAIN;
