/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.19: Write a program reverse(s) that reverses the character string s. Use it to write a program that reverses its input a line at a time.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>
#define MAXLINE 1000
#define MINLINE 80

int getlines(char line[], int max);
void reverse_string(char s[]);

int main()
{
    int len ; 
    char line[MAXLINE];

    while ((len = getlines(line, MAXLINE)) > 0){
        reverse_string(line);
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

void reverse_string(char s[]){
    int index; 
    index = 0;
    while (s[index] != '\0')
        ++index ;
    --index;
    if (s[index] == '\n')
        --index;
    for(int i = index ; i != -1 ; --i)
        printf("%c", s[i]);
    printf("\n");
}
