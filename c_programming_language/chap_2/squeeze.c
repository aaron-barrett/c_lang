#include <stdio.h>

void squeeze (char s[], char c)
{
    int i, j;
    for(i = j = 0 ; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    s[j] = '\0';
}

int main()
{
    char s[] = "abcdeffg";
    char c = 'f';
    printf("%s\n",s);
    squeeze(s,c);
    printf("%s after removing %c\n",s,c);
    return 0;
}