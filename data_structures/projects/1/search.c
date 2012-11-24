#include "search.h"
#include "list.h"

int sequential_search(int *list, int target, int n)
{
    int i;
    for (i = 0;i <= n;i++)
        if (list[i] == target)
            return i;
    return -1;
}

void sequential(int length)
{
    int *list = build_ascending_list(length);
    sequential_search(list, length, length);
    drop_list(list);
}

int ibinary_search(int *list, int target, int n)
{
    int left, right, mid;
    left = 0; right = n;

    while (left <= right) {
        mid = (left + right) >> 1;
        if (list[mid] == target)
            return mid;
        if (list[mid] < target)
            left = mid + 1;
        if (list[mid] > target)
            right = mid - 1;
    }
    return -1;
}

void ibinary(int length)
{
    int *list = build_ascending_list(length);
    ibinary_search(list, length, length);
    drop_list(list);
}

int _rbinary_search(int *list, int target, int left, int right)
{
    if (left > right)
        return -1;

    int mid = (left + right) >> 1;
    if (list[mid] == target)
        return mid;
    if (list[mid] > target)
        return _rbinary_search(list, target, left, mid - 1);
    if (list[mid] < target)
        return _rbinary_search(list, target, mid + 1, right);

    return -1;
}

int rbinary_search(int *list, int target, int n)
{
    return _rbinary_search(list, target, 0, n);
}

void rbinary(int length)
{
    int *list = build_ascending_list(length);
    rbinary_search(list, length, length);
    drop_list(list);
}
