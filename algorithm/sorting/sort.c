#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "select.h"
#include "heap.h"

#define PRINT_ELEMENT(a) printf("%lf ", a)
#define PRINT_LAST_ELEMENT(a) printf("%lf\n", a)
#define READ_ELEMENT(a) scanf("%lf", a)
#define BEGIN copy(array, raw, n); start = clock()
#define END(name) end = clock(); printf(name ": %d %lfs\n",\
                  check(array, sorted, n), (end - start) / 1e6)

static void print(element_t *array, int n);
static void read(element_t *array, int n);
static int check(element_t *array, element_t *sorted, int n);
static void copy(element_t *dest, const element_t *src, int n);

static int cmp(void *a, void *b);

int main()
{
    int n;
    element_t *array, *sorted, *raw;
    clock_t start, end;

    scanf("%d", &n);
    array = malloc(sizeof(element_t) * n);
    sorted = malloc(sizeof(element_t) * n);
    raw = malloc(sizeof(element_t) * n);
    read(raw, n);
    read(sorted, n);

    BEGIN;
    select_sort(array, n, cmp);
    END("select");

    BEGIN;
    heap_sort(array, n, cmp);
    END("heap");
    
    BEGIN;
    heap_sort_no_recur(array, n, cmp);
    END("heap no recurison");

    /*
    print(sorted, n);
    print(array, n);
    */
    free(array);
    free(sorted);
    free(raw);

    return 0;
}

static void print(element_t *array, int n)
{
    int i;

    for (i = 0;i < n - 1;i++)
        PRINT_ELEMENT(array[i]);
    PRINT_LAST_ELEMENT(array[n - 1]);
}

static void read(element_t *array, int n)
{
    int i;

    for (i = 0;i < n;i++)
        READ_ELEMENT(&array[i]);
}

static int check(element_t *array, element_t *sorted, int n)
{
    int i;

    for (i = 0;i < n;i++)
        if (array[i] != sorted[i])
            return 0;
    return 1;
}

static void copy(element_t *dest, const element_t *src, int n)
{
    int i;

    for (i = 0;i < n;i++)
        dest[i] = src[i];
}

static int cmp(void *a, void *b)
{
    element_t va, vb;
    va = *((element_t *) a);
    vb = *((element_t *) b);

    if (va CMP_OP vb)
        return 1;
    if (vb CMP_OP va)
        return -1;
    return 0;
}

void swap(element_t *a, element_t *b)
{
    element_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
