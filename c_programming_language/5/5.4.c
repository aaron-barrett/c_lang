#include <stdio.h>

int strend(char* s, char* t)
{
    size_t size_sstr = 0;
    size_t size_tstr = 0;
    while(*++s != '\0')
        size_sstr++;
    while(*++t != '\0')
        size_tstr++;
    if (size_sstr < size_tstr)
            return 0;
    for(; size_tstr != -1; size_tstr--)
        if (*--s != *--t)
            return 0;
    return 1;
}

int main()
{
    char* s = "First String";
    char* t = "String";
    char* u = "SString";

    if (strend(s,t) == 1)
        printf("\"%s\" appears at the end of \"%s\".\n", t,s);
    else
        printf("\"%s\" does not appears at the end of \"%s\".\n", t,s);

    if (strend(s,u) == 1)
        printf("\"%s\" appears at the end of \"%s\".\n", u,s);
    else
        printf("\"%s\" does not appears at the end of \"%s\".\n", u,s);

    return 0;
}