/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.8: Write a program to count blanks, tabs, and newlines.
*   
*   Notes:
*********************************************************************************************************************************************/
#include<stdio.h>

int main()
{
    int c;
    int new_line = 0;
    int tab = 0;
    int blanks = 0;
    while ((c = getchar()) != EOF){
        if (c == '\n')
            ++new_line;
        if (c == '\t')
            ++tab;
        if (c == ' ')
            ++blanks;
    }
    printf("new line count = %d\n", new_line);
    printf("tab count = %d\n", tab);
    printf("space count = %d\n", blanks);
    return 0;
}
