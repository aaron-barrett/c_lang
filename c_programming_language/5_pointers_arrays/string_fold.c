#include <stdio.h>
#include <ctype.h>

int strcmp_(char* s, char* t)
{
    int i;
        for(i = 0; (tolower(s[i]) == tolower(t[i])) ; i++)
            if (s[i] == '\0')
                return 0;
        return tolower(s[i]) - tolower(t[i]);
}

int main()
{
    char* s = "Aa";
    char* t = "aas";
    printf("%s and %s fold: %d", s,t,strcmp_(s,t));
    return 0;
}