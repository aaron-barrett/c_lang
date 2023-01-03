#include <stdio.h>
#define MAXLINE 1000

int getlines(char line[], int max);
void copy(char to[], char from[]);

int main()
{
    int len ; 
    int max ; 
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getlines(line, MAXLINE)) > 0)
        if (len > max){
            max = len;
            copy(longest, line);
        }

    if (max > 0){
        printf("Max input length is  %d.\n", max);
        printf("%s", longest);
    }
    return 0;
}

int getlines(char s[], int lim)
{
    int c, i;
    for(i = 0 ; (i < lim-1) && (c=getchar()) != EOF && c != '\n' ; ++i)
        s[i] = c;
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    if (c != '\n' && c != EOF)
        while ((c=getchar()) != EOF && c != '\n')
            ++i;
    return i;
}

void copy(char to[], char from[])
{
    int i ; 
    i = 0;
    while ( (to[i] = from[i]) != '\0')
        ++i;
}