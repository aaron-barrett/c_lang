#include <stdio.h>



int main()
{
    char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
    printf("daytab[1][2] = %d.\n", daytab[2][13]);
    printf("*(daytab[1] + 2) = %d.\n", *(daytab[1] + 2) );
    printf("*(*(daytab + 1)+2) = %d.\n", *(*(daytab + 1) + 2) );
    return 0;
}
