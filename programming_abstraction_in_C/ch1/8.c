#include <stdio.h>

void prime_factorization(int num);

int main()
{
    int num;

    printf("Enter number to be factored: ");
    scanf("%d", &num);
    prime_factorization(num);

    return 0;
}

void prime_factorization(int num)
{
    int i, previous;

    for (i = 2, previous = 1;i <= num;)
        if (num % i == 0) {
            if (previous != 1)
                printf("%d * ", previous);
            previous = i;
            num /= i;
        } else {
            i++;
        }
    printf("%d", previous);
}
