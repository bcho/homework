/* double bubble sort
 * (and bubble sort)
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 500
#define RANGE 1000

void bubble_sort(int a[], int length);
void double_bubble_sort(int a[], int length);

void generate_random_number(int a[], int limit);
void print(int a[], int length);

int main()
{
    int a[MAX], length;

    srand(time(NULL));
    length = 10;
    generate_random_number(a, length);
    print(a, length);

    double_bubble_sort(a, length);
    print(a, length);

    return 0;
}

void print(int a[], int length)
{
    int i;
    for (i = 0;i < length;i++)
        printf("%d ", a[i]);
    printf("\n");
}

void generate_random_number(int a[], int limit)
{
    int i;
    for (i = 0;i < limit;i++)
        a[i] = rand() % RANGE;
}

static void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int a[], int length)
{
    int i, j;

    for (i = 0;i < length - 1;i++)
        for (j = 0;j < length - i - 1;j++)
            if (a[j] > a[j + 1])
                swap(&a[j], &a[j + 1]);
}

/* time complexity ~ O(n^2) */
void double_bubble_sort(int a[], int length)
{
    int i, j , k;
    for (i = 0;i < length / 2;i++)
        for (j = i;j < length - i - 1;j++)
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                /* if find a smaller bubble, float it to the i-smallest */
                for (k = j;k > i;k--)
                    if (a[k] < a[k - 1])
                        swap(&a[k], &a[k - 1]);
                    /* if it is not smaller than previous, stop floating */
                    else
                        break;
        }
}
