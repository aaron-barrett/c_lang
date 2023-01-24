/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.15: Rewrite the temperature conversion program of section 1.2 to use a function for conversion.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

float f_to_c(float fahr){
    return (5.0/9.0)*(fahr - 32.0);
}

int main()
{
    float fahr, celsius, lower, upper, step;
    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;
    printf("  F  C\n");
    while (fahr <= upper){
        celsius = f_to_c(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
