#include <ctype.h>
#include <stdio.h>

int atoi(char s[])
{
    int i, n, sign;
    for(i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 *n + (s[i] - '0');
    return sign*n;
}

int main()
{
    char s[] = "\t-1234";
    printf("%s\n", s);
    printf("%d\n", atoi(s));
    return 0;
}