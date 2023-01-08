#include <stdio.h>

/* month_name: return name of n-th month */
char* month_name(int n)
{
    static char* name[] = {
        "Illegal Month", 
        "January", "February", "March", 
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main()
{
    int number = 2;
    char* month = month_name(number);
    printf("Month %d of year is %s.\n", number, month);
    return 0;
}