#include <stdio.h>
#define MAXLINE 1000

int getlines(char line[], int max);
void escape(char to[], char from[]);
void escape_reversal(char to[], char from[]);

int main()
{
    int len ; 
    int max ; 
    char line[MAXLINE];
    char line_escaped[MAXLINE];

    max = 0;
    while ((len = getlines(line, MAXLINE)) > 0){
            printf("\nOriginal Line: \n%s\n", line);
            escape(line, line_escaped);
            printf("\nLine after escape: \n%s\n", line_escaped);
            escape_reversal(line, line_escaped);
            printf("\nLine after escape reversal: \n%s\n", line_escaped);
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

void escape(char from[], char to[])
{
    int from_counter = 0;
    int to_counter = 0;
    while ( from[from_counter] != '\0'){
        switch(from[from_counter]){
            case '\n':
                to[to_counter] = '\\';
                ++to_counter;
                to[to_counter] = 'n';
                ++to_counter;
                ++from_counter;
                break;
            case '\t':
                to[to_counter] = '\\';
                ++to_counter;
                to[to_counter] = 't';
                ++to_counter;
                ++from_counter;
                break;
            default:
                to[to_counter] = from[from_counter];
                ++to_counter;
                ++from_counter;
                break;
        }
    }
    to[to_counter] = from[from_counter];
}

void escape_reversal(char from[], char to[])
{
    int from_counter = 0;
    int to_counter = 0;
    while ( from[from_counter] != '\0'){
        switch(from[from_counter]){
            case 'n':
                if (from[from_counter-1] == '\\'){
                    to[to_counter-1] = '\n';
                    ++from_counter;
                    break;
                }
            case 't' :
                if(from[from_counter-1] == '\\'){
                    to[to_counter] = '\t';
                    ++from_counter;
                    break;
                }
            default:
                to[to_counter] = from[from_counter];
                ++to_counter;
                ++from_counter;
                break;
        }
    }
    to[to_counter] = from[from_counter];
}