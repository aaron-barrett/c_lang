#include <stdio.h>

int setbits(unsigned x, int p, int n, unsigned y)
{
    return 0;
}

int main()
{
    // unsigned x = 0b1110111; // 0b not necessarily in the standard
    int x = 0b1110111;
    int p = 4; 
    int n = 3;
    unsigned y = 0b1110111;
    int result = setbits(x,p,n,y);
}