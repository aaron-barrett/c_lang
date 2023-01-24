/*********************************************************************************************************************************************
*   C Programming Language, Kernighan & Ritchie 
*   
*   4.7: Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it 
*   just use ungetch?
*   
*   Notes: It needs to know about bufp in order to avoid overflow, probably.
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
    else 
        buf[bufp++] = c;
}

void ungets(char s[])
{
    int string_size = strlen(s);
    if (BUFSIZE - bufp < string_size)
        printf("Not enough size in buffer.\n");
    else
        while (string_size > 0 )
            ungetch(s[--string_size]);
}


int main()
{
    char s[] = "This is to use ungets.\n";
    int c;
    ungets(s);
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}
