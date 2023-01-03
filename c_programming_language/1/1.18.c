#include <stdio.h>
#define MAXLINE 1000
#define MINLINE 80

int getlines(char line[], int max);

int main()
{
    int len ; 
    char line[MAXLINE];

    while ((len = getlines(line, MAXLINE)) > 0){
        printf("Line length is  %d.\n", len);
        printf("%s", line);
    }
    return 0;
}

int getlines(char s[], int lim)
{
    int c, i;
    for(i = 0 ; (i < lim-1) && (c=getchar()) != EOF && c != '\n' ; ++i)
        if (c != '\t')
            s[i] = c;
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    if ( c == '\n'){
        while(s[i-2] == ' ')
            --i;
        s[i-1] = '\n';
        s[i] = '\0';
    }
    else 
        s[i] = '\0';
    return i;
}
