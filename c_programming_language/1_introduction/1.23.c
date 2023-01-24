/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.23: Write a progrma to remove all comments from a c program. Don't forget to handled quoted strings and character constants properly.
*   C comments do not nest.
*   
*   Notes: 
*********************************************************************************************************************************************/
#include <stdio.h>
#define MAXLINE 1000

int remove_comments(char line[], int max);

int main()
{
    char line[MAXLINE];
    while ((remove_comments(line, MAXLINE)) > 0)
        printf("%s", line);

    return 0;
}

int remove_comments(char s[], int lim)
{
    int c, i;
    i = 0;
    int comment_block_counter = 0;
    int single_block_comment = 0;
    while(i < lim-1 && (c=getchar()) != EOF && c != '\n'){
        if (c == '*' && s[i-1] == '/'){
            comment_block_counter = comment_block_counter + 1;
            --i;
        }
        else if (c == '/' && s[i-1] == '*')
            comment_block_counter = comment_block_counter - 1;
        else if (c == '/' && s[i-1] == '/'){
            single_block_comment = 1;
            --i;
        }
        if (single_block_comment == 1)
            if (c == '\n')
                single_block_comment = 0;
        if (comment_block_counter == 0 && single_block_comment == 0){
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

