/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.22: Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the
*   n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before
*   the specified column.
*   
*   Notes: 
*********************************************************************************************************************************************/
#include <stdio.h>
#define MAXLINE 1000
#define TABSTOP 8
#define MAXCOLUMN 4

int fold(char line[], int max);

int main()
{
    char line[MAXLINE];
    while ((fold(line, MAXLINE)) > 0)
        printf("\n%s", line);

    return 0;
}

int fold(char s[], int lim)
{
    int c;
    int i = 0;
    int new_word_index = 0;
    int tab_count = 0;
    int char_count = 0;
    while(i < lim-1 && (c=getchar()) != EOF && c != '\n'){
        if(c == '\t'){
            tab_count = tab_count % TABSTOP;
            tab_count = TABSTOP - tab_count;
            char_count = char_count + tab_count;
            tab_count = 0;
        }
        else {
            ++tab_count;
            ++char_count;
        }
        if ((s[i-1] == ' ' || s[i-1] == '\t' || s[i-1] == '\n') && (s[i] != ' ' || s[i] != '\t' || s[i] != '\n') )
            new_word_index = i;
        s[i] = c;
        ++i;
        if (char_count == TABSTOP*MAXCOLUMN){
            if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
                s[i] = '\n';
            else {
                for(int j = i; j > new_word_index; --j)
                    s[j] = s[j-1];
                s[new_word_index] = '\n';
            }
            char_count = 0;
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
