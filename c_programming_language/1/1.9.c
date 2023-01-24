/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.9: Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.
*   
*   Notes:
*********************************************************************************************************************************************/
#include<stdio.h>

int main()
{
    int c;
    int blanks = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ')
            ++blanks;
        else {
            if (blanks != 0){
                putchar(' ');
                blanks = 0;
            }
            putchar(c);
        }
    return 0;
}
