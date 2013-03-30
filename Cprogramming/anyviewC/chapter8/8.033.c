#include <stdio.h>

int month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    int m, d;

    month_day(2000, 364, &m, &d);
    printf("%d %d", m, d);

    return 0;
}

inline int isleap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
    static int mday[2][12] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
    int month;

    if (yearday < 1 || (yearday > 365 && (!isleap(year) && yearday == 366)))
        return 0;

    for (month = 0;yearday > mday[isleap(year)][month];) {
        yearday -= mday[isleap(year)][month];
        month = (month + 1) % 12;
    }
    if (yearday == 0) {
        *pmonth = month;
        *pday = mday[isleap(year)][month - 1];
    } else {
        *pmonth = month + 1;
        *pday = yearday;
    }

    return 1;
}
