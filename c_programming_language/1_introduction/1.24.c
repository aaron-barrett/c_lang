/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.24: Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets, and braces. Dont' forget 
*   about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality.)
*   
*   Notes: Honestly have no idea how to check escape sequences. It might mean to check output after a '\', but I didn't do that. 
*   A very simple test is contained in 1.24_tests
*********************************************************************************************************************************************/
#include <stdio.h>
#define MAXLINE 1000

int check_syntax(char line[], int max);

int main()
{
    char line[MAXLINE];
    while ((check_syntax(line, MAXLINE)) > 0)
        printf("%s", line);
    return 0;
}

int check_syntax(char s[], int lim)
{
    int c, i;
    i = 0;
    int comment_block_counter = 0;
    int parenthesis_counter = 0;
    int bracket_counter = 0;
    int brace_counter = 0;
    int single_quote_counter = 0;
    int double_quote_counter = 0;
    int single_block_comment = 0;
    while(i < lim-1 && (c=getchar()) != EOF){
        if (c == '*' && s[i-1] == '/')
            comment_block_counter++;
        else if (c == '/' && s[i-1] == '*')
            comment_block_counter--;
        else if (c == '/' && s[i-1] == '/')
            single_block_comment = 1;
        if (single_block_comment == 1)
            if (c == '\n')
                single_block_comment = 0;
        if (comment_block_counter == 0 && single_block_comment == 0)
            if (c == '{')
                brace_counter++;
            else if (c == '}')
                brace_counter--;
            else if (c == '(')
                parenthesis_counter++;
            else if (c == ')')
                parenthesis_counter--;
            else if (c == '[')
                bracket_counter++;
            else if (c == ']')
                bracket_counter--;
            else if (c == '\'')
                single_quote_counter++;
            else if (c == '\"')
                double_quote_counter++;
        s[i++] = c;
    }
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    if (c != '\n' && c != EOF)
        while ((c=getchar()) != EOF && c != '\n')
            ++i;
    if (comment_block_counter != 0)
        printf("Comment Block Error - Nonmatching\n");
    if (brace_counter != 0)
        printf("Braces Error - Nonmatching\n");
    if (parenthesis_counter != 0)
        printf("Parenthesis Error - Nonmatching\n");
    if (bracket_counter != 0)
        printf("Bracket Error - Nonmatching\n");
    if (single_quote_counter % 2 != 0)
        printf("Single Quote Error - Nonmatching\n");
    if (double_quote_counter % 2 != 0)
        printf("Double Quote Error - Nonmatching\n");
    int success_message = comment_block_counter + brace_counter + parenthesis_counter + bracket_counter; 
    single_quote_counter = (single_quote_counter % 2);
    double_quote_counter = (double_quote_counter % 2);
    success_message = success_message + single_quote_counter + double_quote_counter;
    if (success_message == 0)
        printf("No Syntax Errors Found in:\n");
    else 
        printf("Syntax Errors Found in:\n");
    return i;
}
