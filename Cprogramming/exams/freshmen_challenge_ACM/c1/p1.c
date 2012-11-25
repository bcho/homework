#include <stdio.h>

int main()
{
    long long n, i, ans;

    scanf("%lld", &n);

    for (ans = 0, i = 1;i <= n;i++)
        ans += i * i;

    printf("%lld\n", ans);

    return 0;
}
