/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.20: Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed
*   set of tab stops, say ever n columns. Should n be a variable or a symbolic parameter?
*   
*   Notes: Symbolic parameter.
*********************************************************************************************************************************************/
#include <stdio.h>
#define MAXLINE 1000
#define TABSTOP 8

int detab(char line[], int max);

int main()
{
    char line[MAXLINE];
    while ((detab(line, MAXLINE)) > 0)
        printf("%s", line);

    return 0;
}

int detab(char s[], int lim)
{
    int c, i,j;
    int tab_count = 0;
    for(i = 0 ; (i < lim-1) && (c=getchar()) != EOF && c != '\n' ; ++i)
        if (c == '\t'){
            tab_count = tab_count % TABSTOP;
            tab_count = TABSTOP - tab_count;
            for(; tab_count != 0; --tab_count){
                s[i] = ' ';
                if (tab_count != 1)
                    ++i;
            }
        }
        else{
            ++tab_count;
            s[i] = c;
        }
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
