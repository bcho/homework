#include <stdio.h>

int main()
{
    int current, largest;

    printf("This program finds the largest integer in a list.\n"
           "Enter 0 to signal the end of the list.\n");

    largest = -(1 << 30);
    do {
        printf(" ? ");
        scanf("%d", &current);
        if (current > largest)
            largest = current;
    } while (current != 0);

    printf("The largest value is %d", largest);

    return 0;
}
