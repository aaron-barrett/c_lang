/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   4.14: Define a maco swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.)
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

#define swap(t,x,y) do{t c = x ; x = y; y = c;} while(0) /* This is a trick to reuse the macro once one instance is called.*/
// #define swap(t,x,y) t c = x ; x = y; y = c // All three swap calls cannot be used at once if this is used.

int main()
{
    int n = 5; 
    int m = 6 ; 
    printf("n = %d \tm = %d\n", n, m);
    swap(int, n, m);
    printf("n = %d \tm = %d\n", n, m);

    char* s1 = "Macros Are";
    char* s2 = "Good";
    printf("%s\t%s\n", s1, s2);
    swap(char*, s1, s2);
    printf("%s\t%s\n", s1, s2);

    double d1 = 6.5;
    double d2 = 8.7;
    printf("n = %f \tm = %f\n", d1, d2);
    swap(double, d1, d2);
    printf("n = %f \tm = %f\n", d1, d2);

    return 0;
}
