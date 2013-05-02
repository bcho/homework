#include <stdio.h>

#define N 550
#define dist(a, b) abs(((a) - (b)))

int quick_select(int *array, int l, int r, int m);
inline static int abs(int a);

int main()
{
    int testcases, n, i, mid, total;
    int street[N];

    scanf("%d", &testcases);
    for (;testcases > 0;testcases--) {
        scanf("%d", &n);
        for (i = 0;i < n;i++)
            scanf("%d", &street[i]);
        mid = quick_select(street, 0, n - 1, (n - 1) / 2);
        for (total = 0, i = 0;i < n;i++)
            total += dist(street[i], mid);
        printf("%d\n", total);
    }

    return 0;
}

inline static void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition(int *array, int l, int r)
{
    int p;

    p = l;
    for (l += 1;l <= r;) {
        if (array[l] > array[p]) {
            swap(&array[l], &array[r]);
            r--;
        } else {
            l++;
        }
    }
    swap(&array[r], &array[p]);
    return r;
}

int quick_select(int *array, int l, int r, int m)
{
    int p;

    if (l > r)
        return -1;
    p = partition(array, l, r);
    if (p == m)
        return array[p];
    if (p > m)
        return quick_select(array, l, p - 1, m);
    return quick_select(array, p + 1, r, m);
}

inline static int abs(int a)
{
    return (a > 0) ? (a) : (-a);
}
