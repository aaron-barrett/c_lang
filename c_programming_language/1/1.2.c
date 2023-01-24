/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   1.2: Experiment to find out what happens when printf's argument string contain \c, where c is some character not listed above. 
*   
*   Notes:
*********************************************************************************************************************************************/
#include <stdio.h>

int main()
{
    printf("Here's a few \\' ' trials: \n");
    printf("Here's a few \\b: \b\n");
    printf("Here's a few \\a: \a\n");
    return 0;
}
