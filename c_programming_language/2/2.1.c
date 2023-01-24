/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   2.1: Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate
*   values fromn standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point
*   types.
*   
*   Notes: TODO: Compute these directly to finish the exercise. Use the size of each type and use binary operations?
*********************************************************************************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    char char_min = CHAR_MIN;
    char char_max = CHAR_MAX;
    short int short_int_min = SHRT_MIN;
    short int short_int_max = SHRT_MAX;
    int int_min = INT_MIN;
    int int_max = INT_MAX;
    long int long_int_min = LONG_MIN;
    long int long_int_max = LONG_MAX;
    float float_min = FLT_MIN;
    float float_max = FLT_MAX;
    double double_min = DBL_MIN;
    double double_max = DBL_MAX;    
    long double long_double_min = LDBL_MIN;
    long double long_double_max = LDBL_MAX;

    printf("char min: %c \t char max: %c\n", char_min, char_max);
    printf("short min: %d \t short max: %d\n", short_int_min, short_int_max);
    printf("int min: %d \t int max: %d\n", int_min, int_max);
    printf("long min: %d \t long max: %d\n", long_int_min, long_int_max);
    printf("float min: %f \t float max: %f\n", float_min, float_max);
    printf("double min: %f \t double max: %f\n", double_min, double_max);
    printf("long double min: %f \t long double max: %f\n", long_double_min, long_double_max);

    return 0;
}
