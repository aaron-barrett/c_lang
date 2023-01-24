/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   4.8: Suppose that there will never be more than one chracter of pushback. Modify getch and ungetch accordingly.
*   
*   Notes:  Having looked this up, I agree with one commenter. "There's too many ways to do this. Just set BUFSIZE to 1".
*********************************************************************************************************************************************/
#include <stdio.h>
#include <string.h>

#define BUFSIZE 1
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
    else 
        buf[bufp++] = c;
}

int main()
{
    int c;
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}
