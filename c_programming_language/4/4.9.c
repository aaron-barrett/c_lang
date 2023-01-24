/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   4.9: Our getch and ungetch do not handle a pushed back EOF correctly. Decide what their properties ought to be if an EOF is pushed back, 
*   then implement your design.
*
*   Notes: 
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void)     /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back to input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else if (c != EOF)
        buf[bufp++] = c;
}

int main()
{
    int c;
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}
