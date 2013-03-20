#include <stdio.h>

typedef enum {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
} weekday_t;

weekday_t previous_day(weekday_t today);
weekday_t next_day(weekday_t today);
weekday_t increment_day(weekday_t start_day, int delta);

int main()
{
    printf("%d\n", previous_day(Monday));
    printf("%d\n", next_day(Sunday));
    printf("%d %d", increment_day(Thursday, 4), increment_day(Monday, -4));

    return 0;
}

weekday_t previous_day(weekday_t today)
{
    return (today - 1 + 7) % 7;
}

weekday_t next_day(weekday_t today)
{
    return (today + 1) % 7;
}

weekday_t increment_day(weekday_t start_day, int delta)
{
    weekday_t (*func)(weekday_t);
    weekday_t next;
    int i;

    if (delta < 0) {
        func = previous_day;
        delta = -delta;
    } else {
        func = next_day;
    }

    for (i = 0, next = start_day;i < delta;i++)
        next = func(next);

    return next;
}
