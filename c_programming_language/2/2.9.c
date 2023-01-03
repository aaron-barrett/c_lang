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