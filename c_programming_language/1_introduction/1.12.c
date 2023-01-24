/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.12: Write a pgoram that prints its input one word per line.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

int main()
{
    int c;
    while((c = getchar()) != EOF)
        if (c != ' ' && c != '\n' && c != '\t')
            putchar(c);
        else
            putchar('\n');
    return 0;
}
