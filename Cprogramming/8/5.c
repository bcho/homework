#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find(int n, int *a[]);
void finish(int *a[], int n);
void print(int *a[], int n);

int main()
{
    int *a[1 << 15];
    int count;

    count = find(4, a);
    print(a, count);
    finish(a, count);

    return 0;   
}

int find(int n, int *a[])
{
    int i, upper, lower, count;

    for (i = 1, lower = 1, upper = 10;i < n;i++) {
        lower *= 10;
        upper *= 10;
    }

    for (i = lower, count = 0;i < upper;i++)
        // if (i * 2 < upper && i * 3 < upper) {
        if (i * 3 < upper) {
            a[count] = malloc(sizeof(int));
            *a[count] = i;
            count++;
        }

    return count;
}

void finish(int *a[], int n)
{
    int i;

    for (i = 0;i < n;i++)
        free(a[i]);
}

void print(int *a[], int n)
{
    int i;

    for (i = 0;i < n;i++)
        printf("%d ", *a[i]);
    printf("\n");
}
