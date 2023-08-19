#include <stdarg.h>
#include <stdio.h>


int sum(int ctr, ...){
    int sum_ints = 0 ; 
    va_list args;
    va_start(args, ctr);
    for(int i = 0 ; i < ctr; i++)
        sum_ints += va_arg(args, int);
    va_end(args);
    return sum_ints;
}


int main(){
    int s = sum(3, 1, 3, 4);
    printf("Sum is %d.\n", s);
    return 0;
}