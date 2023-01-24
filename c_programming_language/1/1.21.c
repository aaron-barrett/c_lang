/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.21: Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same placing. 
*   Use the same tab stops as detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference.
*   
*   Notes: Going by memory, I think a single blank was preferable. 
*********************************************************************************************************************************************/
#include <stdio.h>
#define MAXLINE 1000
#define TABSTOP 8

int entab(char line[], int max);

int main()
{
    char line[MAXLINE];
    while ((entab(line, MAXLINE)) > 0)
        printf("%s", line);

    return 0;
}

int entab(char s[], int lim)
{
    int c, i;
    i = 0;
    int tab_count = 0;
    int space_count = 0;
    while(i < lim-1 && (c=getchar()) != EOF && c != '\n'){
        if (c == ' ')
            ++space_count;
        else{
            if(space_count != 0){
                tab_count = tab_count % TABSTOP;
                if (space_count ==  TABSTOP - tab_count){
                    s[i] = '\t';
                    ++i;
                }
                else 
                    for(; space_count != 0; --space_count){
                        s[i] = ' ';
                        ++i;
                    }
                space_count = 0;
            }
            ++tab_count;
            s[i] = c;
            ++i;
        }

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
