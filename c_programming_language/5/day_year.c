#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for(i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month day: set month, day from day of year */
void month_day(int year, int yearday, int* pmonth, int* pday)
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for(i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

int main()
{
    int month = 0;
    int day = 0;
    int year = 2023;
    int day_count = 7;
    printf("Year = %d \t Day = %d\n", year, day_count);
    month_day(year, day_count, &month, &day);
    printf("Month = %d \t Day = %d\n", month, day);

    month = 2;
    day = 18;
    printf("Month = %d \t Day = %d\n", month, day);
    day_count = day_of_year(year, month, day);
    printf("Year = %d \t Day = %d\n", year, day_count);
    return 0;
}