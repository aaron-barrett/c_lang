#include <stdio.h>
#define MAXLINE 1000
#define MINLINE 80

int getlines(char line[], int max);
void copy(char to[], char from[]);

int main()
{
    int len ; 
    char line[MAXLINE];

    while ((len = getlines(line, MAXLINE)) > 0){
        if (len > MINLINE){
            printf("Line length is  %d.\n", len);
            printf("%s", line);
        }
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
