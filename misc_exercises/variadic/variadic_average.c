#include <stdarg.h>
#include <stdio.h>
#include <string.h>


double average(int ctr, ...){
    double ave = 0;
    va_list args;
    va_start(args, ctr);
    for(int i = 0 ; i < ctr; i++)
        ave += va_arg(args, double);
    va_end(args);
    return ave /= ctr;
}


int main(){
    double ave = average(3, 1.0, 2.0, 3.0);
    printf("Average: %f\n", ave);
    return 0;
}
