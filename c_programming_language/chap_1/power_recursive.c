#include <stdio.h>

float powers(float base, int pow){
    if (pow == 0)
        return 1.0;
    if (pow == 1)
        return base;
    if (pow == -1)
        return 1 / base;
    if (pow > 1)
        return base * powers(base, pow - 1);
    else if (pow < -1)
        return 1/base * powers(base, pow + 1);
}

int main()
{
    printf("2^3 = %3.0f\n", powers(2,3));
    printf("2^-3 = %3.3f\n", powers(2,-3));
    printf("2^0 = %3.3f\n", powers(2,0));
    printf("2^1 = %3.3f\n", powers(2,1));
    return 0;
}