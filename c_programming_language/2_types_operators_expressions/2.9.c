/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   2.9: In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster
*   version of bitcount.
*   
*   Notes: (x-1) and x differ by exactly one bit. &= stores x & (x-1) in x, which now has one less bit than that before. 
*********************************************************************************************************************************************/
#include <stdio.h>

int bitcount(unsigned x)
{
    int b = 0;
    while (x){
        x &= (x-1);
        b++;
    }
    return b;
}

int main()
{
    unsigned x = 7;
    int result = bitcount(x);
    printf("%d bitcount is %d\n", x, result);
    return 0;
}
