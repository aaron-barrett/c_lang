/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   5.9: Rewrite the routines day_of_year and month_day with pointers instead of indexing. 
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>

char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (month < 1 || month > 12){
        printf("Invalid month: %d\n.", month);
        return -1;
    }
    if (day < 1 || day > daytab[leap][month]){
        if (month == 2 ){
            char leap_msg[18] = "(leap year: ";
            if (leap == 1)
                strcat(leap_msg,"yes)");
            else 
                strcat(leap_msg, "no)");
            printf("Invalid day \"%d\" for month \"%d\" %s.\n", day, month, leap_msg);
        }
        else
            printf("Invalid day \"%d\" for month \"%d\"\n.", day, month);
        return -1;
    }

    for(i = 1; i < month; i++)
        day += *(*(daytab+leap)+i);
    return day;
}

/* month day: set month, day from day of year */
void month_day(int year, int yearday, int* pmonth, int* pday)
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if ((yearday > 365) || (yearday > 366 && leap == 1) ){
        char leap_msg[18] = "(leap year: ";
        if (leap == 1)
            strcat(leap_msg,"yes)");
        else 
            strcat(leap_msg, "no)");
        printf("Invalid yearday \"%d\" for year \"%d\" %s.\n", yearday, year, leap_msg);
        return ;
    }

    for(i = 1; yearday >*(*(daytab+leap)+i); i++)
        yearday -=  *(*(daytab+leap)+i);
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
