/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.4: Write a program to print the corresponding Celsius to Fahrenheit table.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

int main()
{
    float fahr, celsius, lower, upper, step;
    lower = -17.8;
    upper = 148.9;
    step = 11.111;
    celsius = lower;
    printf("   C\tF\n");
    while (celsius <= upper){
        fahr = (9.0/5.0)*celsius + 32.0 ;
        printf("%4.1f %6.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}
