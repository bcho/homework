#include <stdio.h>

#define MAX 100

void func(char *s1, int m, char *s2);
void sort(int l, int r, char a[]);

int main()
{
    char s1[MAX] = "deadbeef", s2[MAX];

    func(s1, 1, s2);
    printf("%s", s2);
    return 0;
}

void swap(char *a, char *b)
{
    char t;
    t = *a;
    *a = *b;
    *b = t;
    return;
}

void sort(int l, int r, char a[])
{
    int i, mid, store_index;

    if (l >= r)
        return;
    mid = (l + r) >> 1;
    swap(&a[mid], &a[r]);
    for (i = l, store_index = l;i < r;i++) {
        if (a[i] < a[r]) {
            swap(&a[i], &a[store_index]);
            store_index++;
        }
    }
    swap(&a[r], &a[store_index]);
    sort(l, store_index - 1, a);
    sort(store_index + 1, r, a);
    return;

}

void func(char *s1, int m, char *s2)
{
    char *head;
    int len;

    head = s2;
    while ((*(s2++) = *(s1++)))
        ;
    s2 = head;
    for (len = 0;s2[len] != '\0';len++)
        ;

    sort(m, len - 2, s2);

    return;
}
