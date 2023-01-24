#include <stdio.h>
#include <string.h>

int count = 0;
char function(char s[])
{
    return s[count++]; /* This shows that an postfixed incrementor is not completed with a return statement */
}

int main()
{
    char s[] = "Return Count.\n";
    while (count != strlen(s))
        printf("%c",s[count]);
    printf("\n");
    return 0;
}