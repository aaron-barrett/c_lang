#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_space(char s[])
{
    int k = 0;
    while (isspace(s[0])){
        while (s[k] != '\0')
            s[k++] = s[k+1];
        k = 0;
    }
    for(int i = 0 ; s[i+1] != '\0'; i++ )
        while (isspace(s[i]) && isspace(s[i+1]))
            for(k = i ; s[k] != '\0' ; k++)
                s[k] = s[k+1];
}

int main()
{
    char s[50] = "  1 2 3  4    5    6";
    char t[50] = "1 2 3 4 5 6";
    printf("%s\n",s);
    remove_space(s);
    printf("%s\n",s);
    printf("%s\n",t);
    return 0;
}