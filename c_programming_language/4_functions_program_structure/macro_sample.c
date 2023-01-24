#include <stdio.h>

#define paste(front, back) front ## back
#define dprint(expr) printf(#expr " = %f\n", expr)

int main()
{
    double n = 5; 
    double m = 6 ; 
    int paste(name,1) =  1000;  /* example of using a macro to generate a token name */
    dprint(n/m);                /* using macro to print this divide statement */
    return 0;
}