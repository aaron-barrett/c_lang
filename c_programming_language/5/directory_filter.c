#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int determine_if_space_or_alnum(char s)
{
    if (isalnum(s) == 0 && isspace(s) == 0)
        return 0;
    else 
        return 1;
}

void directory_filter(char *s)
{
    int k = 0;
    for(int i = 0 ; s[i] != '\0'; i++ )
        while ((isalnum(s[i]) == 0 && isspace(s[i]) == 0) && s[i] != '\0')
            for(k = i ; s[k] != '\0' ; k++)
                s[k] = s[k+1];
}

int main()
{  
    // char s[] = "   $@1  @$%^ 2Z &";
    char s[] = "$@1  @$%^ 2B";
    // char s[] = "a$@1  @$%^ 2";
    printf("%s\n",s);
    directory_filter(s);
    printf("%s\n",s);
    return 0;
}

$@1$Z&
$@1@$%^B
$@1@$c%