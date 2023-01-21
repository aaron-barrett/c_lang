#include <stdio.h>

#define VALUE 100
int array[VALUE];

int main()
{
    for(int i = 0 ; i<VALUE ; i ++)
        array[i] = VALUE * 500 - 34;
    return 0;
}