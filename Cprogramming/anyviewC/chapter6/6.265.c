#include <stdio.h>

#define N 8

void sort(int l, int r, int a[], int reverse);
void print(int a[]);
void swap(int *a, int *b);

int main()
{
    int n = N - 1, i;
    int a[N] = {1, 5, 9, 2, 3, 12, 5};

    sort(0, n / 2 - 1, a, 1);
    if (N % 2) {
        sort((n + 1) / 2, n - 1,  a, 0);
    } else {
        sort(n / 2, n - 1, a, 0);
    }
    for (i = 0, a[n] = 0;i < n;i++)
        a[n] += a[i];
    a[n] /= n;
    print(a);

    return 0;
}

void swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
    return;
}

void print(int a[])
{
    int i;
    for (i = 0;i < N;i++)
        printf("%d ", a[i]);
    printf("\n");

    return;
}

void sort(int l, int r, int a[], int reverse)
{
    int i, mid, store_index, cmp;

    if (l >= r)
        return;
    mid = (l + r) >> 1;
    swap(&a[mid], &a[r]);
    for (i = l, store_index = l;i < r;i++) {
        if (reverse)
            cmp = (a[i] > a[r]);
        else
            cmp = (a[i] < a[r]);
        if (cmp) {
            swap(&a[i], &a[store_index]);
            store_index++;
        }
    }
    swap(&a[r], &a[store_index]);
    sort(l, store_index - 1, a, reverse);
    sort(store_index + 1, r, a, reverse);
    return;
}
