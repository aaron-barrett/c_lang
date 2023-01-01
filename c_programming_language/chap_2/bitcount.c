#include <stdio.h>

int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if ( x & 01)
            b++;
    return b;
}

int main()
{
    unsigned x = 5;
    int result = bitcount(x);
    printf("%d bitcount is %d\n", x, result);
    return 0;
}