/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   2.10: Rewrite the function lower, whicih converts upper case letters to lower case, with a conditional expression instead of if-else.
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

int lower (int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A': c;
}

int main()
{
    char c = 'E';
    char cap_c = lower(c);
    printf("%c to lower case is %c.\n", c, cap_c);
    return 0;
}
