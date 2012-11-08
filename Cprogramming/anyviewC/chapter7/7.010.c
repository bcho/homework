#include <stdio.h>

int min(int x, int y, int z);

int main()
{
    printf("%d", min(5, 2, 9));

    return 0;
}

int min(int x, int y, int z)
{
    int _m;

    _m = x;
    if (_m > y) _m = y;
    if (_m > z) _m = z;
    return _m;
}
