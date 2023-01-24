/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   2.2: Write a loop equivalent to the for loop above without using && or ||.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

#define MAXLINE 1000

int main()
{
    int i, c;
    char s[MAXLINE];
    for(i = 0 ; (i < MAXLINE-1) * ((c=getchar()) != EOF) * (c != '\n') == 1 ; ++i)
    // for(i = 0 ; (i < MAXLINE-1), (c=getchar()) != EOF, c != '\n' ; ++i)
    // for(i = 0 ; (i < MAXLINE-1) && (c=getchar()) != EOF && c != '\n' ; ++i)
        s[i] = c;
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    printf("%s\n",s);
    return 0;
}
