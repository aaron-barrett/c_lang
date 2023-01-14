#include <stdio.h>

const int func(const int i)
{
    return i;
}

int main()
{
    /* list of absurdly complicated BUT VALID qualifier statements.*/
    int x_5 = 5;

    const int x = 5;
    int const xx = 5;

    int const* xxx = &xx;
    const int* xxxx = &x;

    int const (*z)();
    const int (*zz)();

    int (*zzz)(const char);
    int (*const zzzz)(const int) = func;

    const int (*const zzzzz)(const int) = func;
    const int* (*const zzzzzz)(const char);

    int *const (*const zzzzzzz)(const char);
    const int *const (*const zzzzzzzz)(const char);
    int* *const (*const zzzzzzzzz)(const char);

    int* *const const (*const zzzzzzzzzz)(const char);
    int* *const const (*const const zzzzzzzzzzz)(const char);
    int* *const const (*const const zzzzzzzzzzzz)(char const*);
    const int* *const const (*const const zzzzzzzzzzzzz)(char const*);

    return 0;
}