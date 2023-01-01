#include <stdio.h>

int lower (int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A': c;
}

int main()
{
    char c = 'E';
    char cap_c = lower(c);
    printf("%c to lower case is %c.\n", c, cap_c);
    return 0;
}